#include "parser.hpp"

#include <algorithm>
#include <array>
#include <ranges>

#include "../../shared/src/ranges_compatibility_layer.hpp"

namespace aoc::day_19 {

[[nodiscard]] static auto parsePatterns(std::string_view input)
    -> std::expected<std::vector<std::string>, std::error_code> {
    std::vector<std::string> patterns;
    auto const lines = std::ranges::views::split(input, ',') | std::ranges::views::transform([](auto const & line) {
                           auto filtered_view = std::ranges::views::drop_while(line, [](auto c) { return c == ' '; });
                           return std::string{filtered_view.begin(), filtered_view.end()};
                       }) |
                       aoc::ranges::to<std::vector<std::string>>;

    for (auto const & line : lines) {
        patterns.push_back(std::string{line.begin(), line.end()});
    }
    return patterns;
}

[[nodiscard]] static auto parseDesigns(std::string_view input)
    -> std::expected<std::vector<std::string>, std::error_code> {
    std::vector<std::string> designs;
    auto const lines = std::ranges::views::split(input, '\n') | std::ranges::views::transform([](auto const & line) {
                           auto str = std::string(line.begin(), line.end());
                           if (str.ends_with('\r')) {
                               return str.substr(0, str.size() - 1);
                           }
                           return str;
                       }) |
                       std::ranges::views::filter([](std::string_view sv) { return !sv.empty(); }) |
                       aoc::ranges::to<std::vector<std::string>>;
    for (auto const & line : lines) {
        designs.push_back(std::string{line.begin(), line.end()});
    }
    return designs;
}

[[nodiscard]] auto parseInput(std::string_view input) -> std::expected<puzzle_input, std::error_code> {
    constexpr auto delimiters = std::array{"\r\n\r\n", "\n\n"};
    auto split_pos =
        std::ranges::find_if(delimiters, [&](auto delim) { return input.find(delim) != std::string_view::npos; });

    if (split_pos == delimiters.end()) {
        return std::unexpected(std::make_error_code(std::errc::invalid_argument));
    }

    auto const split_at = input.find(*split_pos);
    auto const patterns = input.substr(0, split_at);
    auto const designs = input.substr(split_at);

    auto parsed_patterns = parsePatterns(patterns);
    if (!parsed_patterns) {
        return std::unexpected(parsed_patterns.error());
    }
    auto parsed_designs = parseDesigns(designs);
    if (!parsed_designs) {
        return std::unexpected(parsed_designs.error());
    }

    return puzzle_input{std::move(*parsed_patterns), std::move(*parsed_designs)};
}

} // namespace aoc::day_19