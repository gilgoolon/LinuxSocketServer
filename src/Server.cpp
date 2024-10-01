#include <thread>
#include <iostream>
#include <algorithm>
#include <signal.h>

#include "server.hpp"
#include "exceptions.hpp"

static Server *_instance;

Server::Server(const int port, const size_t max_connections)
    : _server_socket(std::make_unique<ServerSocket>(port)), _max_connections(max_connections), _running(true)
{
    struct sigaction action;
    action.sa_handler = server_signal_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    sigaction(SIGINT, &action, nullptr);

    _instance = this;
}

void Server::run()
{
    _server_socket->listen(_max_connections);
    while (_running)
    {
        try
        {
            auto client_socket = _server_socket->accept();
            _active_connections.push_back(std::move(client_socket));
            std::cout << "Client connected" << std::endl;
            std::thread client_handler_thread(&Server::handle_client, this, std::ref(_active_connections.back()));
            client_handler_thread.detach();
        }
        catch (const std::exception &ex)
        {
            std::cout << "Failed to connect new client. Error: " << ex.what() << std::endl;
        }
    }
}

Server &Server::get_instance()
{
    return *_instance;
}

void Server::handle_client(const std::unique_ptr<Socket> &client_socket)
{
    try
    {
        while (_running)
        {
            const auto buff = client_socket->receive();
            client_socket->send(buff);
        }
    }
    catch (const ClientDisconnectedException &ex)
    {
        std::cout << "Client disconnected" << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cout << "Failed to handle client. Error: " << ex.what() << std::endl;
    }
    std::remove(_active_connections.begin(), _active_connections.end(), client_socket), _active_connections.end();
}

void Server::singal_handler(int signal)
{
    if (signal == SIGINT)
    {
        std::cout << "Gracefully shutting down..." << std::endl;
        _running = false;
        _server_socket->shutdown();
        std::for_each(_active_connections.begin(), _active_connections.end(), [](const auto &socket)
                      { socket->shutdown(); });
    }
}

void Server::server_signal_handler(int signal)
{
    get_instance().singal_handler(signal);
}
