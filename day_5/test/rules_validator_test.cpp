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

TEST_F(RulesValidatorTest, HandlesComplexRuleSet) {
    std::vector<aoc::day_5::page_ordering_rule> complex_rules{{1, 2}, {2, 3}, {3, 4}, {4, 5}};
    aoc::day_5::rules_validator complex_validator{complex_rules};

    aoc::day_5::page_update update{{5, 4, 3, 2, 1}};
    EXPECT_FALSE(complex_validator.validate_and_fix(update));
    EXPECT_THAT(update.updateValues, ElementsAre(1, 2, 3, 4, 5));
}