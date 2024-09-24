#pragma once
#include "common/server_socket.hpp"
#include "common/socket.hpp"

class Server
{
public:
    explicit Server(std::unique_ptr<ServerSocket> server_socket, size_t max_connections);

    void run() const;

private:
    std::unique_ptr<ServerSocket> m_server_socket;
    size_t m_max_connections;

    void handle_client(std::unique_ptr<Socket> client_socket) const;
};

std::unique_ptr<Server> create_server(int port, size_t max_connections);
