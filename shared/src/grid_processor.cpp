#include "grid_processor.hpp"

[[nodiscard]] auto aoc::grid_processor::processLines(std::string const & input) -> std::vector<std::string_view> {
    return input | std::views::split('\n') | std::views::transform([](auto && chars) {
               auto sv = std::string_view(chars.begin(), chars.end());
               return sv.ends_with('\r') ? sv.substr(0, sv.size() - 1) : sv;
           }) |
           std::ranges::to<std::vector>();
}

[[nodiscard]] auto aoc::grid_processor::validateGrid(std::span<std::string_view const> lines) -> bool {
    return !std::ranges::any_of(lines, [&lines](auto const & line) { return line.size() != lines.front().size(); });
}