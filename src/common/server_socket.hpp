#pragma once
#include <netinet/in.h>
#include <memory>

#include "socket.hpp"
#include "auto_fd.hpp"

class ServerSocket final
{
public:
    explicit ServerSocket(int port);

    void listen(size_t max_connections) const;

    std::unique_ptr<Socket> accept() const;

    void shutdown();

private:
    const AutoFd _socket_fd;
};
