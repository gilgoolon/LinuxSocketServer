#pragma once
#include <exception>
#include <string>
#include <cstring>
#include <cerrno>
#include <sstream>

class ErrnoException : public std::exception
{
public:
    ErrnoException(int errnum = errno);

    const char *what() const noexcept override;

private:
    const int m_errnum;
    const std::string m_message;
};