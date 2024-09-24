#pragma once
#include <netinet/in.h>
#include <memory>

#include "socket.hpp"

class ServerSocket
{
public:
    explicit ServerSocket(int socket_fd);

    ~ServerSocket();

    void listen(size_t max_connections) const;

    std::unique_ptr<Socket> accept() const;

private:
    int m_socket_fd;
};
