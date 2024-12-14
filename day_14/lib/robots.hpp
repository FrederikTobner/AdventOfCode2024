#pragma once

#include <cstdint>
#include <expected>
#include <string_view>
#include <system_error>

#include "../../shared/src/vector2d.hpp"

#include "../../shared/src/parsing_rules.hpp"

namespace aoc::day_14 {

struct robot {
    aoc::math::vector_2d<int16_t> position;
    aoc::math::vector_2d<int16_t> velocity;

    auto update(size_t x_size, size_t y_size) -> void {
        position += velocity;
        if (position.x < 0) {
            position.x += x_size;
        }
        if (position.y < 0) {
            position.y += y_size;
        }
        if (position.x >= x_size) {
            position.x -= x_size;
        }
        if (position.y >= y_size) {
            position.y -= y_size;
        }
    }
};

auto parseCoordinate(std::string_view line) -> std::expected<aoc::math::vector_2d<int16_t>, std::error_code> {
    auto delimiter = line.find(',');
    auto x = aoc::parser::rules::parse_number<int16_t>(line.substr(0, delimiter));
    auto y = aoc::parser::rules::parse_number<int16_t>(line.substr(delimiter + 1));
    if (!x || !y) {
        return std::unexpected(x.error() ? x.error() : y.error());
    }
    return aoc::math::vector_2d<int16_t>{*x, *y};
}

// Format p=74,51 v=36,-94
auto parseRobot(std::string_view line) -> std::expected<robot, std::error_code> {
    robot r;
    auto [x, y] = aoc::math::vector_2d<int16_t>{};
    auto [vx, vy] = aoc::math::vector_2d<int16_t>{};

    auto pos_start = line.find("p=") + 2;
    auto pos_end = line.find(" v=");

    auto vel_start = pos_end + 3;
    auto vel_end = line.size();

    auto pos = line.substr(pos_start, pos_end - pos_start);
    auto vel = line.substr(vel_start, vel_end - vel_start);

    auto parsed_pos = parseCoordinate(pos);

    if (!parsed_pos) {
        return std::unexpected(parsed_pos.error());
    }

    auto parsed_vel = parseCoordinate(vel);

    if (!parsed_vel) {
        return std::unexpected(parsed_vel.error());
    }

    r.position = *parsed_pos;
    r.velocity = *parsed_vel;

    return r;
}

} // namespace aoc::day_14
