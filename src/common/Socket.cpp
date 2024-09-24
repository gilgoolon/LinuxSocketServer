#include "Socket.h"
#include <unistd.h>


Socket::Socket(int socket_fd)
    : m_socket_fd(socket_fd)
{
}

Socket::~Socket()
{
    ::close(m_socket_fd);
}

void Socket::send(const Buffer &data) const
{
}

Buffer Socket::receive() const
{
    return Buffer();
}
