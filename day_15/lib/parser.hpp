#pragma once

#include <array>
#include <expected>
#include <ranges>
#include <string_view>
#include <system_error>
#include <utility>
#include <vector>

#include "../../shared/src/direction.hpp"
#include "../../shared/src/ranges_compatibility_layer.hpp"

#include "cell_type.hpp"

namespace aoc::day_15 {

auto parse_input(std::string_view input)
    -> std::expected<std::pair<std::string_view, std::string_view>, std::error_code> {
    constexpr auto delimiters = std::array{"\r\n\r\n", "\n\n"};
    auto split_pos =
        std::ranges::find_if(delimiters, [&](auto delim) { return input.find(delim) != std::string_view::npos; });

    if (split_pos == delimiters.end()) {
        return std::unexpected(std::make_error_code(std::errc::invalid_argument));
    }

    auto const split_at = input.find(*split_pos);
    return std::pair{input.substr(0, split_at), input.substr(split_at)};
}

auto parse_warehouse(std::string_view input) -> std::vector<std::vector<cell_type>> {
    auto warehouse = std::vector<std::vector<cell_type>>{};

    for (auto const & line : input | std::views::split('\n')) {
        auto row = std::vector<cell_type>{};
        for (auto const & cell : line) {
            switch (cell) {
            case '.':
                row.push_back(cell_type::EMPTY);
                break;
            case '#':
                row.push_back(cell_type::WALL);
                break;
            case 'O':
                row.push_back(cell_type::BOX);
                break;
            case '@':
                row.push_back(cell_type::ROBOT);
                break;
            default:
                break;
            }
        }
        warehouse.push_back(row);
    }

    return warehouse;
}

auto parse_movements(std::string_view input) -> std::vector<aoc::math::Direction> {
    auto movements = std::vector<aoc::math::Direction>{};

    for (auto const & c : input) {
        switch (c) {
        case '^':
            movements.push_back(aoc::math::Direction::UP);
            break;
        case 'v':
            movements.push_back(aoc::math::Direction::DOWN);
            break;
        case '<':
            movements.push_back(aoc::math::Direction::LEFT);
            break;
        case '>':
            movements.push_back(aoc::math::Direction::RIGHT);
            break;
        default:
            break;
        }
    }

    return movements;
}

} // namespace aoc::day_15