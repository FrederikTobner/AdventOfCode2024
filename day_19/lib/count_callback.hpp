#pragma once

#include <cstdint>
#include <optional>
#include <string_view>

#include "matcher.hpp"

namespace aoc::day_19 {

struct count_callback {
    pattern_matcher * matcher;
    [[nodiscard]] auto handle_max_depth() const -> size_t;
    [[nodiscard]] auto handle_empty() const -> size_t;
    [[nodiscard]] auto check_cache(std::string_view design) const -> std::optional<size_t>;
    [[nodiscard]] auto initial_value() const -> size_t;
    [[nodiscard]] auto process_match(std::string_view next_design, size_t next_depth, size_t current_total) const
        -> size_t;
    [[nodiscard]] auto should_break(size_t) const -> bool;
    auto update_cache(std::string_view design, size_t result) -> void;
};

} // namespace aoc::day_19
