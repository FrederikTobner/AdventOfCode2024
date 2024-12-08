#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../lib/equation_puzzle_solver.hpp"

#include <span>

using namespace aoc::day_7;

class EquationPuzzleSolverTest : public ::testing::Test {};

TEST_F(EquationPuzzleSolverTest, BasicAddition) {
    // Arrange
    equation_puzzle<> puzzle{equation_result<>{15}, {7, 8}};

    // Act
    auto solution = solveEquationPuzzle<size_t>(puzzle, aoc::day_7::BASIC_OPERATORS<>);

    // Assert
    ASSERT_TRUE(solution);
    ASSERT_EQ(solution->size(), 1);
    EXPECT_EQ((*solution)[0]->type, operation_type::add);
}

TEST_F(EquationPuzzleSolverTest, BasicMultiplication) {
    // Arrange
    equation_puzzle puzzle{equation_result<>{42}, {6, 7}};

    // Act
    auto solution = solveEquationPuzzle<size_t>(puzzle, aoc::day_7::BASIC_OPERATORS<>);

    // Assert
    ASSERT_TRUE(solution);
    ASSERT_EQ(solution->size(), 1);
    EXPECT_EQ((*solution)[0]->type, operation_type::multiply);
}

TEST_F(EquationPuzzleSolverTest, Concatenation) {
    // Arrange
    equation_puzzle puzzle{equation_result<>{42}, {4, 2}};

    // Act
    auto isSolvableUsingBasicOperators = isSolvable<size_t>(puzzle, aoc::day_7::BASIC_OPERATORS<>);
    auto isSolvableUsingAllOperators = isSolvable<size_t>(puzzle, aoc::day_7::ALL_OPERATORS<>);

    auto solution = solveEquationPuzzle<size_t>(puzzle, aoc::day_7::ALL_OPERATORS<>);

    // Assert
    EXPECT_FALSE(isSolvableUsingBasicOperators);
    EXPECT_TRUE(isSolvableUsingAllOperators);
    ASSERT_TRUE(solution);
    ASSERT_EQ(solution->size(), 1);
    EXPECT_EQ((*solution)[0]->type, operation_type::concat);
}

TEST_F(EquationPuzzleSolverTest, ComplexExpression) {
    // Arrange
    equation_puzzle puzzle{equation_result<>{142}, {1, 4, 2}};

    // Act
    auto solution = solveEquationPuzzle<size_t>(puzzle, aoc::day_7::ALL_OPERATORS<>);

    // Assert
    ASSERT_TRUE(solution);
    ASSERT_EQ(solution->size(), 2);
}

TEST_F(EquationPuzzleSolverTest, EmptyPuzzle) {
    // Arrange
    equation_puzzle puzzle{equation_result<>{0}, {}};

    // Act
    auto result = solveEquationPuzzle<size_t>(puzzle, aoc::day_7::BASIC_OPERATORS<>);

    // Assert
    EXPECT_FALSE(result);
    EXPECT_EQ(result.error(), std::errc::invalid_argument);
}

TEST_F(EquationPuzzleSolverTest, UnsolvablePuzzle) {
    // Arrange
    equation_puzzle puzzle{equation_result<>{10}, {1, 2, 3}};

    // Act
    auto result = solveEquationPuzzle<size_t>(puzzle, aoc::day_7::BASIC_OPERATORS<>);

    // Assert
    EXPECT_FALSE(result);
    EXPECT_EQ(result.error(), std::errc::result_out_of_range);
}
