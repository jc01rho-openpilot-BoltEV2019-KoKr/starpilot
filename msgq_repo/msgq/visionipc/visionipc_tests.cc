#include <thread>
#include <chrono>
#include <atomic>
#include <future>

#include <sys/socket.h>
#include <unistd.h>

#include "catch2/catch.hpp"

#include "msgq/visionipc/visionipc_server.h"
#include "msgq/visionipc/visionipc_client.h"


static void zmq_sleep(int milliseconds=1000){
  if (messaging_use_zmq()){
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
  }
}

TEST_CASE("Connecting"){
  VisionIpcServer server("camerad");
  server.create_buffers(VISION_STREAM_ROAD, 1, 100, 100);
  server.start_listener();

  VisionIpcClient client = VisionIpcClient("camerad", VISION_STREAM_ROAD, false);
  REQUIRE(client.connect());

  REQUIRE(client.connected);
}

TEST_CASE("Nonblocking connect times out when server does not reply"){
  const std::string name = "camerad";
  const std::string ipc_path = get_ipc_path(name);
  int listener_fd = ipc_bind(ipc_path.c_str());
  REQUIRE(listener_fd >= 0);

  std::atomic<bool> request_received = false;
  std::promise<void> release_server;
  auto release_future = release_server.get_future();
  std::thread unresponsive_server([&] {
    int client_fd = accept(listener_fd, nullptr, nullptr);
    if (client_fd >= 0) {
      VisionStreamType type = VISION_STREAM_MAX;
      int result = ipc_sendrecv_with_fds(false, client_fd, &type, sizeof(type), nullptr, 0, nullptr);
      request_received = result == sizeof(type);
      release_future.wait();
      close(client_fd);
    }
    close(listener_fd);
    unlink(ipc_path.c_str());
  });

  VisionIpcClient client(name, VISION_STREAM_ROAD, false);
  auto started = std::chrono::steady_clock::now();
  bool connected = client.connect(false);
  auto elapsed = std::chrono::steady_clock::now() - started;

  release_server.set_value();
  unresponsive_server.join();

  REQUIRE(request_received);
  REQUIRE_FALSE(connected);
  REQUIRE(elapsed < std::chrono::seconds(2));
}

TEST_CASE("Server survives clients that disconnect during handshake"){
  VisionIpcServer server("camerad");
  server.create_buffers(VISION_STREAM_ROAD, 1, 100, 100);
  server.start_listener();

  VisionIpcClient first_client("camerad", VISION_STREAM_ROAD, false);
  REQUIRE(first_client.connect());

  const std::string ipc_path = get_ipc_path("camerad");
  int disconnected_fd = ipc_connect(ipc_path.c_str());
  REQUIRE(disconnected_fd >= 0);
  close(disconnected_fd);

  int abandoned_fd = ipc_connect(ipc_path.c_str());
  REQUIRE(abandoned_fd >= 0);
  VisionStreamType type = VISION_STREAM_ROAD;
  REQUIRE(ipc_sendrecv_with_fds(true, abandoned_fd, &type, sizeof(type), nullptr, 0, nullptr) == sizeof(type));
  close(abandoned_fd);

  VisionIpcClient recovered_client("camerad", VISION_STREAM_ROAD, false);
  REQUIRE(recovered_client.connect());
}

TEST_CASE("getAvailableStreams"){
  VisionIpcServer server("camerad");
  server.create_buffers(VISION_STREAM_ROAD, 1, 100, 100);
  server.create_buffers(VISION_STREAM_WIDE_ROAD, 1, 100, 100);
  server.start_listener();
  auto available_streams = VisionIpcClient::getAvailableStreams("camerad");
  REQUIRE(available_streams.size() == 2);
  REQUIRE(available_streams.count(VISION_STREAM_ROAD) == 1);
  REQUIRE(available_streams.count(VISION_STREAM_WIDE_ROAD) == 1);
}

TEST_CASE("Check buffers"){
  size_t width = 100, height = 200, num_buffers = 5;
  VisionIpcServer server("camerad");
  server.create_buffers(VISION_STREAM_ROAD, num_buffers, width, height);
  server.start_listener();

  VisionIpcClient client = VisionIpcClient("camerad", VISION_STREAM_ROAD, false);
  REQUIRE(client.connect());

  REQUIRE(client.buffers[0].width == width);
  REQUIRE(client.buffers[0].height == height);
  REQUIRE(client.buffers[0].len);
  REQUIRE(client.num_buffers == num_buffers);
}

TEST_CASE("Send single buffer"){
  VisionIpcServer server("camerad");
  server.create_buffers(VISION_STREAM_ROAD, 1, 100, 100);
  server.start_listener();

  VisionIpcClient client = VisionIpcClient("camerad", VISION_STREAM_ROAD, false);
  REQUIRE(client.connect());
  zmq_sleep();

  VisionBuf * buf = server.get_buffer(VISION_STREAM_ROAD);
  REQUIRE(buf != nullptr);

  *((uint64_t*)buf->addr) = 1234;

  VisionIpcBufExtra extra = {0};
  extra.frame_id = 1337;
  buf->set_frame_id(extra.frame_id);

  server.send(buf, &extra);

  VisionIpcBufExtra extra_recv = {0};
  VisionBuf * recv_buf = client.recv(&extra_recv);
  REQUIRE(recv_buf != nullptr);
  REQUIRE(*(uint64_t*)recv_buf->addr == 1234);
  REQUIRE(extra_recv.frame_id == extra.frame_id);
  REQUIRE(recv_buf->get_frame_id() == extra.frame_id);
}


TEST_CASE("Test no conflate"){
  VisionIpcServer server("camerad");
  server.create_buffers(VISION_STREAM_ROAD, 1, 100, 100);
  server.start_listener();

  VisionIpcClient client = VisionIpcClient("camerad", VISION_STREAM_ROAD, false);
  REQUIRE(client.connect());
  zmq_sleep();

  VisionBuf * buf = server.get_buffer(VISION_STREAM_ROAD);
  REQUIRE(buf != nullptr);

  VisionIpcBufExtra extra = {0};
  extra.frame_id = 1;
  server.send(buf, &extra);
  extra.frame_id = 2;
  server.send(buf, &extra);

  VisionIpcBufExtra extra_recv = {0};
  VisionBuf * recv_buf = client.recv(&extra_recv);
  REQUIRE(recv_buf != nullptr);
  REQUIRE(extra_recv.frame_id == 1);

  recv_buf = client.recv(&extra_recv);
  REQUIRE(recv_buf != nullptr);
  REQUIRE(extra_recv.frame_id == 2);
}

TEST_CASE("Test conflate"){
  VisionIpcServer server("camerad");
  server.create_buffers(VISION_STREAM_ROAD, 1, 100, 100);
  server.start_listener();

  VisionIpcClient client = VisionIpcClient("camerad", VISION_STREAM_ROAD, true);
  REQUIRE(client.connect());
  zmq_sleep();

  VisionBuf * buf = server.get_buffer(VISION_STREAM_ROAD);
  REQUIRE(buf != nullptr);

  VisionIpcBufExtra extra = {0};
  extra.frame_id = 1;
  server.send(buf, &extra);
  extra.frame_id = 2;
  server.send(buf, &extra);

  VisionIpcBufExtra extra_recv = {0};
  VisionBuf * recv_buf = client.recv(&extra_recv);
  REQUIRE(recv_buf != nullptr);
  REQUIRE(extra_recv.frame_id == 2);

  recv_buf = client.recv(&extra_recv);
  REQUIRE(recv_buf == nullptr);
}
