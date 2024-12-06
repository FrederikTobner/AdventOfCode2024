#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../lib/grid_parser.hpp"

using namespace aoc::day_6;
using namespace testing;

class GridParserTest : public Test {
  protected:
    std::vector<std::string_view> makeGrid(std::initializer_list<std::string_view> lines) {
        return {lines.begin(), lines.end()};
    }
};

TEST_F(GridParserTest, ParsesValidGridWithGuardUp) {
    auto grid = makeGrid({
        "...",
        ".^.",
        "...",
    });

    auto result = parseGrid(grid);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->guardPosition.first, 1);
    EXPECT_EQ(result->guardPosition.second, 1);
    EXPECT_EQ(result->guardDirection, FacingDirection::Up);
}

struct GuardDirectionTestParams {
    char guardChar;
    FacingDirection expectedDirection;
    std::string testName;

    static auto toString(testing::TestParamInfo<GuardDirectionTestParams> const & info) -> std::string {
        return info.param.testName;
    }
};

TEST_F(GridParserTest, RejectsMultipleGuards) {
    auto grid = makeGrid({
        "^..",
        ".>.",
    });

    auto result = parseGrid(grid);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), "Multiple guards found in grid");
}

TEST_F(GridParserTest, RejectsNoGuard) {
    auto grid = makeGrid({
        "...",
        "...",
    });

    auto result = parseGrid(grid);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), "No guard found in grid");
}

TEST_F(GridParserTest, RejectsInvalidCharacter) {
    auto grid = makeGrid({
        "..x",
        ".^.",
    });

    auto result = parseGrid(grid);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), "Invalid tile type");
}
