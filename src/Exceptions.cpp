#include "Exceptions.h"

ErrnoException::ErrnoException(int errnum)
    : m_errnum(errnum)
{
    std::ostringstream oss;
    oss << "Errno " << m_errnum << ": " << std::strerror(m_errnum);
    m_message = oss.str();
}

const char *ErrnoException::what() const noexcept
{
    return m_message.c_str();
}
