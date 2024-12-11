#include "parsing_error.hpp"

namespace aoc::day_11 {

char const * ParsingErrorCategory::name() const noexcept {
    return "parsing_error";
}

std::string ParsingErrorCategory::message(int ev) const {
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

std::error_code std::make_error_code(aoc::day_11::ParsingError e) {
    return {static_cast<int>(e), aoc::day_11::ParsingErrorCategory::get()};
}