#include <cerrno>
#include <chrono>

#include <sys/socket.h>
#include <unistd.h>

#include "catch2/catch.hpp"

#include "msgq/visionipc/visionipc.h"

#ifdef __APPLE__
static constexpr int TEST_SOCKET_TYPE = SOCK_STREAM;
#else
static constexpr int TEST_SOCKET_TYPE = SOCK_SEQPACKET;
#endif

TEST_CASE("IPC receive returns when peer does not reply") {
  int sockets[2] = {-1, -1};
  REQUIRE(socketpair(AF_UNIX, TEST_SOCKET_TYPE, 0, sockets) == 0);

  char data = 0;
  auto started = std::chrono::steady_clock::now();
  errno = 0;
  int result = ipc_sendrecv_with_fds(false, sockets[0], &data, sizeof(data), nullptr, 0, nullptr, 50);
  auto elapsed = std::chrono::steady_clock::now() - started;

  close(sockets[0]);
  close(sockets[1]);

  REQUIRE(result == -1);
  REQUIRE(errno == ETIMEDOUT);
  REQUIRE(elapsed < std::chrono::seconds(1));
}

TEST_CASE("IPC send to a closed peer returns an error") {
  int sockets[2] = {-1, -1};
  REQUIRE(socketpair(AF_UNIX, TEST_SOCKET_TYPE, 0, sockets) == 0);
  close(sockets[1]);

  char data = 0;
  int result = ipc_sendrecv_with_fds(true, sockets[0], &data, sizeof(data), nullptr, 0, nullptr, 50);
  close(sockets[0]);

  REQUIRE(result == -1);
}
