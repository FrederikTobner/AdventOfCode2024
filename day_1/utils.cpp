
#include "utils.hpp"

constexpr auto isWhitespace(char c) noexcept -> bool 
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}