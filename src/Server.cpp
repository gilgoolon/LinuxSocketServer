#include <thread>

#include "Server.h"

Server::Server(std::unique_ptr<ServerSocket> server_socket, size_t max_connections)
    : m_server_socket(std::move(server_socket)), m_max_connections(max_connections)
{
}

void Server::run() const
{
    m_server_socket->listen(m_max_connections);
    while (true)
    {
        auto client_socket = m_server_socket->accept();
        std::thread client_handler_thread(&Server::handle_client, this, std::move(client_socket));
        client_handler_thread.detach();
    }
}

void Server::handle_client(const std::unique_ptr<Socket> client_socket) const
{
    const auto buff = client_socket->receive();
    client_socket->send(buff);
}

std::unique_ptr<Server> create_server(const int port, const size_t max_connections)
{
    return std::make_unique<Server>(create_server_socket(port), max_connections);
}
