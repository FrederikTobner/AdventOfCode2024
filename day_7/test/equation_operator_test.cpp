#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../lib/equation_operator.hpp"

using namespace aoc::day_7;

TEST(EquationOperatorTest, Addition) {
    // Arrange
    auto const & add_op = equationOperators_t<>[static_cast<size_t>(operation_type::add)];

    // Act
    auto result = add_op.apply(equation_result<>{5}, equation_result<>{3});

    // Assert
    EXPECT_EQ(add_op.type, operation_type::add);
    EXPECT_EQ(add_op.name, " + ");
    EXPECT_EQ(result.getRawValue(), 8);
}

TEST(EquationOperatorTest, Multiplication) {
    // Arrange
    auto const & mul_op = equationOperators_t<>[static_cast<size_t>(operation_type::multiply)];

    // Act
    auto result = mul_op.apply(equation_result<>{5}, equation_result<>{3});

    // Assert
    EXPECT_EQ(mul_op.type, operation_type::multiply);
    EXPECT_EQ(mul_op.name, " * ");
    EXPECT_EQ(result.getRawValue(), 15);
}

TEST(EquationOperatorTest, Concatenation) {
    // Arrange
    auto const & concat_op = equationOperators_t<>[static_cast<size_t>(operation_type::concat)];

    // Act
    auto result = concat_op.apply(equation_result<>{5}, equation_result<>{3});

    // Assert
    EXPECT_EQ(concat_op.type, operation_type::concat);
    EXPECT_EQ(concat_op.name, " || ");
    EXPECT_EQ(result.getRawValue(), 53);
}

TEST(EquationOperatorTest, BasicOperatorsContainAddAndMultiply) {
    // Assert
    ASSERT_EQ(std::size(BASIC_OPERATORS_T<>), 2);
    EXPECT_EQ(BASIC_OPERATORS_T<>[0] -> type, operation_type::add);
    EXPECT_EQ(BASIC_OPERATORS_T<>[1] -> type, operation_type::multiply);
}

TEST(EquationOperatorTest, AllOperatorsContainBasicPlusConcat) {
    // Assert
    ASSERT_EQ(std::size(ALL_OPERATORS_T<>), 3);
    EXPECT_EQ(ALL_OPERATORS_T<>[0] -> type, operation_type::add);
    EXPECT_EQ(ALL_OPERATORS_T<>[1] -> type, operation_type::multiply);
    EXPECT_EQ(ALL_OPERATORS_T<>[2] -> type, operation_type::concat);
}