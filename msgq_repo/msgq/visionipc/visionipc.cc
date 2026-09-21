#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>

#include <sys/mman.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/un.h>

#ifdef __APPLE__
#define getsocket() socket(AF_UNIX, SOCK_STREAM, 0)
#else
#define getsocket() socket(AF_UNIX, SOCK_SEQPACKET, 0)
#endif

#include "msgq/visionipc/visionipc.h"

static int poll_socket(int fd, short events, int timeout_ms) {
  struct pollfd poll_fd = {
    .fd = fd,
    .events = events,
  };

  int result;
  do {
    result = poll(&poll_fd, 1, timeout_ms);
  } while (result < 0 && errno == EINTR);

  if (result == 0) {
    errno = ETIMEDOUT;
    return -1;
  }
  if (result < 0) {
    return -1;
  }
  if (poll_fd.revents & events) {
    return 0;
  }
  if (poll_fd.revents & (POLLERR | POLLHUP | POLLNVAL)) {
    errno = ECONNRESET;
    return -1;
  }
  errno = EIO;
  return -1;
}

int ipc_connect(const char* socket_path, int timeout_ms) {
  int err;

  int sock = getsocket();

  if (sock < 0) return -1;
  int flags = -1;
  if (timeout_ms >= 0) {
    flags = fcntl(sock, F_GETFL, 0);
    if (flags < 0 || fcntl(sock, F_SETFL, flags | O_NONBLOCK) < 0) {
      close(sock);
      return -1;
    }
  }
  struct sockaddr_un addr = {
    .sun_family = AF_UNIX,
  };
  snprintf(addr.sun_path, sizeof(addr.sun_path), "%s", socket_path);
  err = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
  if (err != 0) {
    err = errno;
    // Unix SOCK_SEQPACKET reports EAGAIN for a full listen backlog, while
    // SOCK_STREAM reports EINPROGRESS for a non-blocking connection.
    if (timeout_ms >= 0 && (err == EINPROGRESS || err == EAGAIN)) {
      if (poll_socket(sock, POLLOUT, timeout_ms) == 0) {
        socklen_t error_len = sizeof(err);
        if (getsockopt(sock, SOL_SOCKET, SO_ERROR, &err, &error_len) < 0) {
          err = errno;
        }
      } else {
        err = errno;
      }
    }
  }
  if (err != 0) {
    close(sock);
    errno = err;
    return -1;
  }
  if (timeout_ms >= 0 && fcntl(sock, F_SETFL, flags) < 0) {
    close(sock);
    return -1;
  }

  return sock;
}

int ipc_bind(const char* socket_path) {
  int err;

  unlink(socket_path);

  int sock = getsocket();

  struct sockaddr_un addr = {
    .sun_family = AF_UNIX,
  };
  snprintf(addr.sun_path, sizeof(addr.sun_path), "%s", socket_path);
  err = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
  assert(err == 0);

  err = listen(sock, 3);
  assert(err == 0);

  return sock;
}


int ipc_sendrecv_with_fds(bool send, int fd, void *buf, size_t buf_size, int* fds, int num_fds,
                          int *out_num_fds, int timeout_ms) {
  char control_buf[CMSG_SPACE(sizeof(int) * num_fds)];
  memset(control_buf, 0, CMSG_SPACE(sizeof(int) * num_fds));

  struct iovec iov = {
    .iov_base = buf,
    .iov_len = buf_size,
  };
  struct msghdr msg = {
    .msg_iov = &iov,
    .msg_iovlen = 1,
  };

  if (num_fds > 0) {
    assert(fds);

    msg.msg_control = control_buf;
    msg.msg_controllen = CMSG_SPACE(sizeof(int) * num_fds);
  }

  if (timeout_ms >= 0 && poll_socket(fd, send ? POLLOUT : POLLIN, timeout_ms) < 0) {
    return -1;
  }

  if (send) {
    if (num_fds) {
      struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);
      assert(cmsg);
      cmsg->cmsg_level = SOL_SOCKET;
      cmsg->cmsg_type = SCM_RIGHTS;
      cmsg->cmsg_len = CMSG_LEN(sizeof(int) * num_fds);
      memcpy(CMSG_DATA(cmsg), fds, sizeof(int) * num_fds);
    }
    int flags = timeout_ms >= 0 ? MSG_DONTWAIT : 0;
#ifdef MSG_NOSIGNAL
    flags |= MSG_NOSIGNAL;
#endif
    return sendmsg(fd, &msg, flags);
  } else {
    int r = recvmsg(fd, &msg, timeout_ms >= 0 ? MSG_DONTWAIT : 0);
    if (r < 0 && timeout_ms >= 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
      errno = ETIMEDOUT;
    }
    if (r < 0) return r;

    int recv_fds = 0;
    if (msg.msg_controllen > 0) {
      struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);
      assert(cmsg);
      assert(cmsg->cmsg_level == SOL_SOCKET && cmsg->cmsg_type == SCM_RIGHTS);
      recv_fds = (cmsg->cmsg_len - CMSG_LEN(0));
      assert(recv_fds > 0 && (recv_fds % sizeof(int)) == 0);
      recv_fds /= sizeof(int);

      assert(fds && recv_fds <= num_fds);
      memcpy(fds, CMSG_DATA(cmsg), sizeof(int) * recv_fds);
    }

    if (msg.msg_flags) {
      for (int i=0; i<recv_fds; i++) {
        close(fds[i]);
      }
      return -1;
    }

    if (fds) {
      assert(out_num_fds);
      *out_num_fds = recv_fds;
    }
    return r;
  }
}
