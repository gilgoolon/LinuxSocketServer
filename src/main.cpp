#include <iostream>

#include "server.hpp"

constexpr int EXPECTED_ARGUMENTS = 2;

int main(const int argc, char **argv)
{
    if (EXPECTED_ARGUMENTS != argc)
    {
        std::cout << "Usage: " << argv[0] << " [port]" << std::endl;
        return EXIT_FAILURE;
    }
    const int server_port = std::stoi(argv[1]);
    const size_t max_connections = 10;
    std::cout << "Running server on port: " << server_port << std::endl;
    try
    {
        const auto server = create_server(server_port, max_connections);
        server->run();
    }
    catch (const std::exception &ex)
    {
        std::cout << "Failed to create/run server. Error: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
