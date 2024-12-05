#include "../lib/safety_check.hpp"
#include <gtest/gtest.h>

class SafetyCheckTest : public testing::TestWithParam<std::pair<std::vector<uint8_t>, bool>> {};

TEST_P(SafetyCheckTest, ValidatesSequenceCorrectly) {
    auto const & [sequence, expected] = GetParam();
    EXPECT_EQ(aoc::day_2::isSafe(sequence), expected) << "Failed for sequence: " << ::testing::PrintToString(sequence);
}

INSTANTIATE_TEST_SUITE_P(SafeSequences, SafetyCheckTest,
                         testing::Values(std::make_pair(std::vector<uint8_t>{7, 6, 4, 2, 1},
                                                        true),                                     // Monotonic decrease
                                         std::make_pair(std::vector<uint8_t>{1, 3, 6, 7, 9}, true) // Monotonic increase
                                         ),
                         [](testing::TestParamInfo<SafetyCheckTest::ParamType> const & info) {
                             return "Safe_" + std::to_string(info.index);
                         });

INSTANTIATE_TEST_SUITE_P(UnsafeSequences, SafetyCheckTest,
                         testing::Values(std::make_pair(std::vector<uint8_t>{1, 2, 7, 8, 9}, false), // Jump too large
                                         std::make_pair(std::vector<uint8_t>{9, 7, 6, 2, 1}, false), // Invalid pattern
                                         std::make_pair(std::vector<uint8_t>{1, 3, 2, 4, 5}, false), // Local minimum
                                         std::make_pair(std::vector<uint8_t>{8, 6, 4, 4, 1}, false) // Duplicate numbers
                                         ),
                         [](testing::TestParamInfo<SafetyCheckTest::ParamType> const & info) {
                             return "Unsafe_" + std::to_string(info.index);
                         });