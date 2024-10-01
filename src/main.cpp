#include <iostream>

#include "server.hpp"

enum ProgramArguments : int
{
    ProgramName,
    PortNumber,
    EndFinal
};

int main(const int argc, char **argv)
{
    if (ProgramArguments::EndFinal != argc)
    {
        std::cout << "Usage: " << argv[ProgramArguments::ProgramName] << " [port]" << std::endl;
        return EXIT_FAILURE;
    }
    int server_port;
    try
    {
        server_port = std::stoi(argv[ProgramArguments::PortNumber]);
    }
    catch (...)
    {
        std::cout << "Please enter a valid port number." << std::endl;
    }
    const size_t max_connections = 10;
    std::cout << "Running server on port: " << server_port << std::endl;
    try
    {
        auto server = Server::get_instance(server_port, max_connections);
        server->run();
    }
    catch (const std::exception &ex)
    {
        std::cout << "Failed to create/run server. Error: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
