#include "match_callback.hpp"

namespace aoc::day_19 {

auto match_callback::handle_max_depth() const -> bool {
    return false;
}
auto match_callback::handle_empty() const -> bool {
    return true;
}
auto match_callback::check_cache(std::string_view design) const -> std::optional<bool> {
    auto it = matcher->m_match_cache.find(design);
    return it != matcher->m_match_cache.end() ? std::optional{it->second} : std::nullopt;
}
auto match_callback::initial_value() const -> bool {
    return false;
}
auto match_callback::process_match(std::string_view next_design, size_t next_depth, bool) const -> bool {
    return matcher->match_recursive(next_design, next_depth);
}
auto match_callback::should_break(bool result) const -> bool {
    return result;
}
auto match_callback::update_cache(std::string_view design, bool result) -> void {
    matcher->m_match_cache[design] = result;
}

} // namespace aoc::day_19