#include <iostream>
#include "Server.h"

constexpr int EXPECTED_ARGUMENTS = 2;

int main(const int argc, char **argv)
{
    if (EXPECTED_ARGUMENTS != argc)
    {
        std::cout << "Usage: " << argv[0] << " [port]" << std::endl;
        return 1;
    }
    const int server_port = std::stoi(argv[1]);
    const size_t max_connections = 10;
    std::cout << "Running server on port: " << server_port << std::endl;
    const auto server = create_server(server_port, max_connections);
    server->run();
    return 0;
}
