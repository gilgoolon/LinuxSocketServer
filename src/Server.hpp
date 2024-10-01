#pragma once
#include <stdint.h>
#include "common/server_socket.hpp"
#include "common/socket.hpp"

constexpr uint32_t OPTIONAL_IGNORED = 0;

class Server final
{
public:
    void run();

    explicit Server(uint32_t port, size_t max_connections);

    static std::shared_ptr<Server> get_instance(uint32_t port, size_t max_connections);

private:
    const std::unique_ptr<ServerSocket> _server_socket;
    const size_t _max_connections;
    std::vector<std::unique_ptr<Socket>> _active_connections;
    bool _running;

    void handle_client(const std::unique_ptr<Socket> &client_socket);

    void singal_handler(int signal);

    static void server_signal_handler(int signal);

    static void register_signal_handler();
};
