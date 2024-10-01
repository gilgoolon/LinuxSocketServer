#pragma once
#include "common/server_socket.hpp"
#include "common/socket.hpp"

class Server final
{
public:
    explicit Server(int port, size_t max_connections);

    void run();

    static Server &get_instance();

private:
    const std::unique_ptr<ServerSocket> _server_socket;
    const size_t _max_connections;
    std::vector<std::unique_ptr<Socket>> _active_connections;
    bool _running;

    void handle_client(const std::unique_ptr<Socket> &client_socket);

    void singal_handler(int signal);

    static void server_signal_handler(int signal);
};
