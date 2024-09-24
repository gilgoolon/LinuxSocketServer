#include "exceptions.hpp"

ErrnoException::ErrnoException(const int errnum)
    : m_errnum(errnum), m_message("Errno " + std::to_string(m_errnum) + ": " + std::strerror(m_errnum))
{
}

const char *ErrnoException::what() const noexcept
{
    return m_message.c_str();
}
