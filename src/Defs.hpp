#pragma once
#include <vector>
#include <cstdint>
#include <cstddef>

using Byte = uint8_t;
using Buffer = std::vector<Byte>;

constexpr int UNIX_INT_ERROR_VALUE = -1;
constexpr size_t DEFAULT_BUFF_SIZE = 4096;
constexpr int DEFAULT_NO_FLAGS = 0;
constexpr nullptr_t OPTIONAL_NO_OUTPUT = nullptr;
