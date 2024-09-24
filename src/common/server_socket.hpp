#pragma once
#include <netinet/in.h>
#include <memory>

#include "socket.hpp"
#include "auto_fd.hpp"

class ServerSocket
{
public:
    explicit ServerSocket(int port);

    void listen(size_t max_connections) const;

    std::unique_ptr<Socket> accept() const;

private:
    AutoFd m_socket_fd;
};
