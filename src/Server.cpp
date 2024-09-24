#include <thread>
#include <iostream>

#include "server.hpp"

Server::Server(const int port, const size_t max_connections)
    : m_server_socket(std::make_unique<ServerSocket>(port)), m_max_connections(max_connections)
{
}

void Server::run() const
{
    m_server_socket->listen(m_max_connections);
    while (true)
    {
        try
        {
            auto client_socket = m_server_socket->accept();
            std::thread client_handler_thread(&Server::handle_client, this, std::move(client_socket));
            client_handler_thread.detach();
        }
        catch (const std::exception &ex)
        {
            std::cout << "Failed to start handling client. Error: " << ex.what() << std::endl;
        }
    }
}

void Server::handle_client(const std::unique_ptr<Socket> client_socket) const
{
    try
    {

        const auto buff = client_socket->receive();
        client_socket->send(buff);
    }
    catch (const std::exception &ex)
    {
        std::cout << "Failed to handle client. Error: " << ex.what() << std::endl;
    }
}
