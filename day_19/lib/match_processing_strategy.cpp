#include "match_processing_strategy.hpp"

namespace aoc::day_19 {

auto match_processing_strategy::handle_max_depth() const -> bool {
    return false;
}
auto match_processing_strategy::handle_empty() const -> bool {
    return true;
}
auto match_processing_strategy::check_cache(std::string_view design) const -> std::optional<bool> {
    auto it = matcher->m_match_cache.find(design);
    return it != matcher->m_match_cache.end() ? std::optional{it->second} : std::nullopt;
}
auto match_processing_strategy::initial_value() const -> bool {
    return false;
}
auto match_processing_strategy::process_match(std::string_view next_design, size_t next_depth, bool) const -> bool {
    return matcher->match_recursive(next_design, next_depth);
}
auto match_processing_strategy::should_break(bool result) const -> bool {
    return result;
}
auto match_processing_strategy::update_cache(std::string_view design, bool result) -> void {
    matcher->m_match_cache[design] = result;
}

} // namespace aoc::day_19