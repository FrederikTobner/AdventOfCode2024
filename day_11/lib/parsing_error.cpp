#include "parsing_error.hpp"

namespace aoc::day_11 {

auto ParsingErrorCategory::name() const noexcept -> char const * {
    return "parsing_error";
}

auto ParsingErrorCategory::message(int ev) const -> std::string {
    switch (static_cast<ParsingError>(ev)) {
    case ParsingError::GenericError:
        return "An error occurred while parsing the input";
    case ParsingError::NoInput:
        return "No input was provided for parsing";
    case ParsingError::TooMuchInput:
        return "Too much input was provided for parsing";
    default:
        return "Unknown parsing error";
    }
}

} // namespace aoc::day_11

auto std::make_error_code(aoc::day_11::ParsingError e) -> std::error_code {
    return {static_cast<int>(e), aoc::day_11::ParsingErrorCategory::get()};
}