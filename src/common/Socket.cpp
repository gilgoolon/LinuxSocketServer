#include <sys/socket.h>
#include <unistd.h>

#include "socket.hpp"
#include "utils.hpp"

Socket::Socket(const int socket_fd)
    : m_socket_fd(make_auto_fd(socket_fd))
{
}

void Socket::send(const Buffer &data) const
{
    covered_call(UNIX_INT_ERROR_VALUE, ::send, *m_socket_fd.get(), data.data(), data.size(), DEFAULT_NO_FLAGS);
}

Buffer Socket::receive() const
{
    Buffer buff;
    while (true)
    {
        const size_t buff_size = DEFAULT_BUFF_SIZE;
        const size_t old_size = buff.size();
        buff.resize(old_size + buff_size);

        const ssize_t bytes_read = covered_call(UNIX_INT_ERROR_VALUE, ::recv, *m_socket_fd.get(), buff.data() + old_size, buff_size, DEFAULT_NO_FLAGS);
        buff.resize(old_size + bytes_read);

        if (bytes_read < buff_size)
        {
            break;
        }
    }
    return buff;
}
