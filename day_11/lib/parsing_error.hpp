#pragma once

#include <string>
#include <system_error>

namespace aoc::day_11 {

/// @brief Enumeration of possible parsing errors
enum class ParsingError {
    GenericError,
    NoInput,
    TooMuchInput,
};

/// @brief Error category for parsing errors
class ParsingErrorCategory : public std::error_category {
  public:
    /// @brief Get the singleton instance of the parsing error category
    /// @return The singleton instance of the parsing error category
    static ParsingErrorCategory const & get() {
        static ParsingErrorCategory instance;
        return instance;
    }

    /// @brief Get the name of the error category
    /// @return The name of the error category
    char const * name() const noexcept override;

    /// @brief Get the message associated with a parsing error
    /// @param ev The error value to get the message for
    /// @return The message associated with the error value
    std::string message(int ev) const override;
};

} // namespace aoc::day_11

namespace std {
/// @brief Specialization of the is_error_code_enum type trait for parsing errors
template <> struct is_error_code_enum<aoc::day_11::ParsingError> : true_type {};

/// @brief Create an error code from a parsing error
/// @param e The parsing error to create an error code from
/// @return The error code created from the parsing error
std::error_code make_error_code(aoc::day_11::ParsingError e);
} // namespace std
