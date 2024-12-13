#include "parser.hpp"

#include <ranges>

#include "../../shared/src/ranges_compatibility_layer.hpp"

namespace aoc::day_12 {
auto parseInput(std::string_view input)
    -> std::expected<std::unordered_map<char, std::unordered_set<aoc::math::vector_2d<int16_t>>>, std::error_code> {
    std::unordered_map<char, std::unordered_set<aoc::math::vector_2d<int16_t>>> result;
    aoc::math::vector_2d<int16_t> current;
    auto lines = input | std::views::split('\n') | std::views::transform([](auto && line) {
                     auto sv = std::string_view(line.begin(), line.end());
                     return sv.ends_with('\r') ? sv.substr(0, sv.size() - 1) : sv;
                 }) |
                 ::aoc::ranges::to<std::vector<std::string_view>>;
    if (lines.size() > UINT8_MAX) {
        return std::unexpected(std::make_error_code(std::errc::invalid_argument));
    }
    for (uint8_t x = 0; x < lines.size(); ++x) {
        auto const & line = lines[x];
        if (line.size() > UINT8_MAX) {
            return std::unexpected(std::make_error_code(std::errc::invalid_argument));
        }
        for (uint8_t y = 0; y < line.size(); ++y) {
            if (result.contains(line[y])) {
                result[line[y]].insert({::aoc::math::vector_2d<int16_t>(x, y)});
            } else {
                result.insert({line[y], {::aoc::math::vector_2d<int16_t>(x, y)}});
            }
        }
    }
    return result;
}
} // namespace aoc::day_12