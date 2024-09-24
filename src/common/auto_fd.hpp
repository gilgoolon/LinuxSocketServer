#pragma once
#include <memory>
#include <unistd.h>

#include "../defs.hpp"

struct FdCloser
{
    void operator()(int *fd) const
    {
        if (UNIX_INT_ERROR_VALUE != *fd)
        {
            ::close(*fd);
        }
    }
};

using AutoFd = std::unique_ptr<int, FdCloser>;

AutoFd make_auto_fd(int fd);
