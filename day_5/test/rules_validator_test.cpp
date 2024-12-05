#include "../lib/rules_validator.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::ElementsAre;

class RulesValidatorTest : public ::testing::Test {
  protected:
    // Rule set where: 1 must come before 2, and 2 must come before 3
    std::vector<aoc::day_5::page_ordering_rule> basic_rules{{1, 2}, {2, 3}};
    aoc::day_5::rules_validator validator{basic_rules};
};

TEST_F(RulesValidatorTest, ValidatesCorrectOrder) {
    aoc::day_5::page_update update{{1, 4, 2, 5, 3}};
    EXPECT_TRUE(validator.validate_and_fix(update));
    EXPECT_THAT(update.updateValues, ElementsAre(1, 4, 2, 5, 3));
}

TEST_F(RulesValidatorTest, FixesAndValidatesSimpleSwap) {
    aoc::day_5::page_update update{{2, 1, 3}};
    EXPECT_FALSE(validator.validate_and_fix(update));
    EXPECT_THAT(update.updateValues, ElementsAre(1, 2, 3));
}

TEST_F(RulesValidatorTest, HandlesMultipleRuleViolations) {
    aoc::day_5::page_update update{{3, 2, 1}};
    EXPECT_FALSE(validator.validate_and_fix(update));
    EXPECT_THAT(update.updateValues, ElementsAre(1, 2, 3));
}

TEST_F(RulesValidatorTest, HandlesMissingElements) {
    aoc::day_5::page_update update{{1, 4, 5}};
    EXPECT_TRUE(validator.validate_and_fix(update));
    EXPECT_THAT(update.updateValues, ElementsAre(1, 4, 5));
}

TEST_F(RulesValidatorTest, HandlesEmptyUpdate) {
    aoc::day_5::page_update update{{}};
    EXPECT_TRUE(validator.validate_and_fix(update));
    EXPECT_TRUE(update.updateValues.empty());
}

TEST_F(RulesValidatorTest, HandlesComplexRuleSet) {
    std::vector<aoc::day_5::page_ordering_rule> complex_rules{{1, 2}, {2, 3}, {3, 4}, {1, 4}};
    aoc::day_5::rules_validator complex_validator{complex_rules};

    aoc::day_5::page_update update{{4, 3, 2, 1}};
    EXPECT_FALSE(complex_validator.validate_and_fix(update));
    EXPECT_THAT(update.updateValues, ElementsAre(1, 2, 3, 4));
}

TEST_F(RulesValidatorTest, HandlesInterleavedElements) {
    aoc::day_5::page_update update{{5, 3, 1, 6, 2, 4}};
    EXPECT_FALSE(validator.validate_and_fix(update));
    // Verify required ordering is maintained while preserving other elements
    auto & result = update.updateValues;
    // Check that 1 comes before 2 and 2 comes before 3
    auto one_pos = std::find(result.begin(), result.end(), 1);
    auto two_pos = std::find(result.begin(), result.end(), 2);
    auto three_pos = std::find(result.begin(), result.end(), 3);
    EXPECT_TRUE(one_pos < two_pos && two_pos < three_pos);
}

TEST_F(RulesValidatorTest, PreservesUnrelatedElements) {
    aoc::day_5::page_update update{{2, 5, 1, 6, 3, 4}};
    EXPECT_FALSE(validator.validate_and_fix(update));
    // Verify unrelated elements (4,5,6) are still present after fixes
    auto & result = update.updateValues;
    EXPECT_NE(std::find(result.begin(), result.end(), 4), result.end());
    EXPECT_NE(std::find(result.begin(), result.end(), 5), result.end());
    EXPECT_NE(std::find(result.begin(), result.end(), 6), result.end());
}
