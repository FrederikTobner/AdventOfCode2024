#pragma once

#include <cstdint>
#include <optional>
#include <string_view>

#include "matcher.hpp"

namespace aoc::day_19 {
struct match_processing_strategy {
    pattern_matcher * matcher;
    [[nodiscard]] auto handle_max_depth() const -> bool;
    [[nodiscard]] auto handle_empty() const -> bool;
    [[nodiscard]] auto check_cache(std::string_view design) const -> std::optional<bool>;
    [[nodiscard]] auto initial_value() const -> bool;
    [[nodiscard]] auto process_match(std::string_view next_design, size_t next_depth, bool) const -> bool;
    [[nodiscard]] auto should_break(bool result) const -> bool;
    auto update_cache(std::string_view design, bool result) -> void;
};
} // namespace aoc::day_19