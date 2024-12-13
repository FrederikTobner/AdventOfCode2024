#include "../lib/parser.hpp"

#include <gtest/gtest.h>

TEST(ParserTest, ParseInput) {
    std::string input = "abc\ndef\nghi";
    auto result = aoc::day_12::parseInput(input);
    ASSERT_TRUE(result.has_value());

    auto const & map = *result;
    EXPECT_EQ(map.size(), 9);
    EXPECT_EQ(map.at('a').size(), 1);
    EXPECT_TRUE(map.at('a').contains({0, 0}));
    EXPECT_TRUE(map.at('e').contains({1, 1}));
    EXPECT_TRUE(map.at('i').contains({2, 2}));
}

TEST(PlantLocationTest, InvalidInput) {
    std::string input(300, 'a'); // Input too large
    auto result = aoc::day_12::parseInput(input);
    EXPECT_FALSE(result.has_value());
}
