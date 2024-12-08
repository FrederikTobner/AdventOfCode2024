#include "../lib/rules_validator.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

struct OrderTestCase {
    std::vector<uint8_t> input;
    std::vector<uint8_t> expected;
    bool should_be_valid;
};

class RulesValidatorTest : public ::testing::TestWithParam<OrderTestCase> {
  protected:
    std::vector<aoc::day_5::page_ordering_rule> basic_rules{{1, 2}, {2, 3}};
    aoc::day_5::rules_validator validator{basic_rules};
};

TEST_P(RulesValidatorTest, ValidatesAndFixesOrder) {
    // Arrange
    auto const & param = GetParam();
    aoc::day_5::page_update update{param.input};

    // Act
    auto result = validator.validate_and_fix(update);

    // Assert
    EXPECT_EQ(result, param.should_be_valid);
    auto const updateIter = update.cbegin();
    for (size_t i = 0; i < param.expected.size(); ++i) {
        EXPECT_EQ(updateIter[i], param.expected[i]);
    }
}

INSTANTIATE_TEST_SUITE_P(OrderingTests, RulesValidatorTest,
                         ::testing::Values(OrderTestCase{{1, 4, 2, 5, 3}, {1, 4, 2, 5, 3}, true},
                                           OrderTestCase{{2, 1, 3}, {1, 2, 3}, false},
                                           OrderTestCase{{3, 2, 1}, {1, 2, 3}, false},
                                           OrderTestCase{{1, 4, 5}, {1, 4, 5}, true},
                                           OrderTestCase{{5, 4, 3, 2, 1}, {5, 4, 1, 2, 3}, false}));

// Add new test fixture for complex rules
class ComplexRulesValidatorTest : public ::testing::TestWithParam<OrderTestCase> {
  protected:
    std::vector<aoc::day_5::page_ordering_rule> complex_rules{{1, 2}, {2, 3}, {3, 4}, {4, 5}};
    aoc::day_5::rules_validator validator{complex_rules};
};

TEST_P(ComplexRulesValidatorTest, ValidatesAndFixesOrder) {
    // Arrange
    auto const & param = GetParam();
    aoc::day_5::page_update update{param.input};

    // Act
    auto result = validator.validate_and_fix(update);

    // Assert
    EXPECT_EQ(result, param.should_be_valid);
    auto const updateIter = update.cbegin();
    for (size_t i = 0; i < param.expected.size(); ++i) {
        EXPECT_EQ(updateIter[i], param.expected[i]);
    }
}

INSTANTIATE_TEST_SUITE_P(ComplexOrderingTests, ComplexRulesValidatorTest,
                         ::testing::Values(OrderTestCase{{5, 4, 3, 2, 1}, {1, 2, 3, 4, 5}, false},
                                           OrderTestCase{{1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, true}));