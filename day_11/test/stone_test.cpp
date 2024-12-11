#include <gtest/gtest.h>

#include "../lib/stone.hpp"

struct StoneTestParam {
    std::vector<size_t> input;
    size_t cycles;
    size_t expected;
    std::string test_name;
};

class StoneTest : public testing::TestWithParam<StoneTestParam> {};

TEST_P(StoneTest, CalculateStones) {
    auto const [input, cycles, expected, test_name] = GetParam();
    EXPECT_EQ(aoc::day_11::calculateStones(input, cycles), expected) << "Failed on test case: " << test_name;
}

INSTANTIATE_TEST_SUITE_P(
    StoneTests, StoneTest,
    testing::Values(
        StoneTestParam{{125, 17}, 6, 22, "simple_input_6_cycles"},
        StoneTestParam{{125, 17}, 25, 55312, "simple_input_25_cycles"},
        StoneTestParam{{0, 27, 5409930, 828979, 4471, 3, 68524, 170}, 25, 194482, "complex_input_25_cycles"},
        StoneTestParam{{0, 27, 5409930, 828979, 4471, 3, 68524, 170}, 75, 232454623677743, "complex_input_75_cycles"}),
    [](testing::TestParamInfo<StoneTest::ParamType> const & info) { return info.param.test_name; });
