#pragma once
#include <netinet/in.h>
#include <memory>
#include "common/Socket.h"

class ServerSocket
{
public:
    explicit ServerSocket(int socket_fd);

    ~ServerSocket();

    void bind(const sockaddr_in &server_address) const;

    void listen(size_t max_connections) const;

    std::unique_ptr<Socket> accept() const;

private:
    int m_socket_fd;
};

std::unique_ptr<ServerSocket> create_server_socket(int port);
