#pragma once
#include "../exceptions.hpp"

template <typename Func, typename... Args>
int covered_call(int error_value, Func func, Args... args)
{
    int result = func(std::forward<Args>(args)...);
    if (error_value == result)
    {
        throw ErrnoException();
    }
    return result;
}
