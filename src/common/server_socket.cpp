#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "server_socket.hpp"
#include "../exceptions.hpp"
#include "utils.hpp"

ServerSocket::ServerSocket(int port)
{
    m_socket_fd = covered_call(UNIX_INT_ERROR_VALUE, &::socket, AF_INET, SOCK_STREAM, DEFAULT_NO_FLAGS);

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = ::htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;
    covered_call(UNIX_INT_ERROR_VALUE, ::bind, m_socket_fd, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address));
}

ServerSocket::~ServerSocket()
{
    ::close(m_socket_fd);
}

void ServerSocket::listen(size_t max_connections) const
{
    covered_call(UNIX_INT_ERROR_VALUE, ::listen, m_socket_fd, max_connections);
}

std::unique_ptr<Socket> ServerSocket::accept() const
{
    return std::make_unique<Socket>(covered_call(UNIX_INT_ERROR_VALUE, ::accept, m_socket_fd, OPTIONAL_NO_OUTPUT, OPTIONAL_NO_OUTPUT));
}
