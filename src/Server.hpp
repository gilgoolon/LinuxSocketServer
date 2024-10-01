#pragma once
#include <stdint.h>
#include "common/server_socket.hpp"
#include "common/socket.hpp"

class Server
{
public:
    void run();

    static void init(uint32_t port, size_t max_connections);

    static std::shared_ptr<Server> get_instance();

private:
    const std::unique_ptr<ServerSocket> _server_socket;
    std::vector<std::unique_ptr<Socket>> _active_connections;
    bool _running;

    static void init_instance();

    explicit Server();

    void handle_client(const std::unique_ptr<Socket> &client_socket);

    void singal_handler(int signal);

    static void server_signal_handler(int signal);

    static void register_signal_handler();
};
