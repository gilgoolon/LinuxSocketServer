#pragma once
#include "../Defs.hpp"

class Socket
{
public:
    explicit Socket(int socket_fd);

    ~Socket();

    void send(const Buffer &data) const;

    Buffer receive() const;

private:
    int m_socket_fd;
};
