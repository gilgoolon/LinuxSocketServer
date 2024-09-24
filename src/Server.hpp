#pragma once
#include "common/server_socket.hpp"
#include "common/socket.hpp"

class Server final
{
public:
    explicit Server(int port, size_t max_connections);

    void run() const;

private:
    const std::unique_ptr<ServerSocket> _server_socket;
    const size_t _max_connections;

    void handle_client(std::unique_ptr<Socket> client_socket) const;
};
