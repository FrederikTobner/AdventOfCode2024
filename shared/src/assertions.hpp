#pragma once

namespace aoc::assertions {

/// @brief Always false concept for static assertions
/// @tparam ...T Variadic template parameter pack
/// @details This concept is used to trigger a static assertion with a custom message
template <class... T> inline constexpr bool always_false = false;

} // namespace aoc::assertions