#pragma once
#include "../buffer.hpp"
#include "auto_fd.hpp"

class Socket final
{
public:
    explicit Socket(int socket_fd);

    void send(const Buffer &data) const;

    Buffer receive() const;

    void shutdown() const;

private:
    const AutoFd _socket_fd;
};
