#include <expected>
#include <ranges>
#include <string>
#include <system_error>
#include <vector>

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"
#include "../../shared/src/ranges_compatibility_layer.hpp"
#include "../../shared/src/vector2d.hpp"

#include "../lib/robots.hpp"
#include "../lib/world.hpp"

auto main(int argc, char const ** argv) -> int {
    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    auto lines = *input | std::views::split('\n') | std::views::transform([](auto && chars) {
        auto sv = std::string_view(chars.begin(), chars.end());
        if (sv.ends_with('\r')) {
            return sv.substr(0, sv.size() - 1);
        }
        return sv;
    }) | std::views::filter([](std::string_view sv) { return !sv.empty(); }) |
                 ::aoc::ranges::to<std::vector<std::string_view>>;

    auto robots = std::vector<aoc::day_14::robot>{};
    for (auto const & line : lines) {
        auto robot = aoc::day_14::parseRobot(line);
        if (!robot) {
            std::println(stderr, "Failed to parse robot: {}", robot.error().message());
            return aoc::EXIT_CODE_DATA_ERROR;
        }
        robots.push_back(*robot);
    }

    auto world = aoc::day_14::world{.robots = robots, .x_size = 101, .y_size = 103};

    for (size_t i = 1; i <= 100 * 103; ++i) {
        world.update();
        if (i == 100) {
            std::println("After 100 seconds the world has a safety score of: {}", world.safetyScore());
        }
        if (world.formsChristmasTree()) {
            std::println("Christmas tree formed after {} seconds", i);
            break;
        }
    }

    return 0;
}
