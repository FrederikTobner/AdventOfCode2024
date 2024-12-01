/**
 * @file exit_code.hpp
 * @brief This file contains the exit codes for the program.
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
