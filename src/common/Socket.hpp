#pragma once
#include "../buffer.hpp"
#include "auto_fd.hpp"

class Socket final
{
public:
    explicit Socket(int socket_fd);

    void send(const Buffer &data) const;

    Buffer receive() const;

private:
    const AutoFd m_socket_fd;
};
