#include "count_callback.hpp"

namespace aoc::day_19 {
auto count_callback::handle_max_depth() const -> size_t {
    return 0;
}
auto count_callback::handle_empty() const -> size_t {
    return 1;
}
auto count_callback::check_cache(std::string_view design) const -> std::optional<size_t> {
    auto it = matcher->m_count_cache.find(design);
    return it != matcher->m_count_cache.end() ? std::optional{it->second} : std::nullopt;
}
auto count_callback::initial_value() const -> size_t {
    return 0;
}
auto count_callback::process_match(std::string_view next_design, size_t next_depth, size_t current_total) const
    -> size_t {
    return current_total + matcher->count_recursive(next_design, next_depth);
}
auto count_callback::should_break(size_t) const -> bool {
    return false;
}
auto count_callback::update_cache(std::string_view design, size_t result) -> void {
    matcher->m_count_cache[design] = result;
}

} // namespace aoc::day_19