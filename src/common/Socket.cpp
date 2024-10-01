#include <sys/socket.h>
#include <unistd.h>

#include "socket.hpp"
#include "utils.hpp"

Socket::Socket(const int socket_fd)
    : _socket_fd(make_auto_fd(socket_fd))
{
}

void Socket::send(const Buffer &data) const
{
    covered_call(UNIX_INT_ERROR_VALUE, ::send, *_socket_fd.get(), data.data(), data.size(), DEFAULT_NO_FLAGS);
}

Buffer Socket::receive() const
{
    Buffer buff;
    const size_t buff_size = DEFAULT_BUFF_SIZE;
    ssize_t bytes_read;
    do
    {
        const size_t old_size = buff.size();
        buff.resize(old_size + buff_size);
        bytes_read = covered_call(UNIX_INT_ERROR_VALUE, ::recv, *_socket_fd.get(), buff.data() + old_size, buff_size, DEFAULT_NO_FLAGS);
        if (!bytes_read)
        {
            throw ClientDisconnectedException();
        }
        buff.resize(old_size + bytes_read);
    } while (bytes_read >= buff_size);
    return buff;
}

void Socket::shutdown() const
{
    covered_call(UNIX_INT_ERROR_VALUE, ::shutdown, *_socket_fd.get(), SHUT_RDWR);
}
