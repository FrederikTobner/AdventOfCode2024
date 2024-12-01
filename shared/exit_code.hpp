/**
 * @file exit_code.hpp
 * @brief Program exit codes definition
 * @details Defines standardized exit codes based on UNIX sysexits,
 * providing meaningful return values for different program termination scenarios.
 */

#pragma once

/// @brief Exit codes based on the sysexits from UNIX
typedef enum {
    /// Signals a successful exit
    EXIT_CODE_SUCCESS = 0,
    /// Signals an error regarding the format of the data
    EXIT_CODE_DATA_ERROR = 65,
    /// Signals an error opening a file
    EXIT_CODE_IO_ERROR = 74,
} exit_code_t;
