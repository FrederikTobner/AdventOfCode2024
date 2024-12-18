#include "../lib/parser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fstream>

using namespace aoc::day_18;

class ParserTest : public ::testing::Test {
  protected:
    void SetUp() override {
        valid_input = "1,2\n3,4\n5,6\n";
        invalid_input = "1,2\nabc,def\n5,6\n";
    }

    std::string valid_input;
    std::string invalid_input;
};

TEST_F(ParserTest, SuccessfullyParsesValidInput) {
    // Arrange
    std::ofstream temp_file("test_input.txt");
    temp_file << valid_input;
    temp_file.close();

    // Act
    auto result = parseInput("test_input.txt");

    // Assert
    ASSERT_TRUE(result.has_value());
    EXPECT_THAT(result->size(), testing::Eq(3));
    EXPECT_THAT((*result)[0], testing::ElementsAre(1, 2));
    EXPECT_THAT((*result)[1], testing::ElementsAre(3, 4));
    EXPECT_THAT((*result)[2], testing::ElementsAre(5, 6));

    std::remove("test_input.txt");
}

TEST_F(ParserTest, HandlesNonExistentFile) {
    // Arrange
    std::string non_existent_file = "does_not_exist.txt";

    // Act
    auto result = parseInput(non_existent_file);

    // Assert
    ASSERT_FALSE(result.has_value());
}

class ParserParameterizedTest
    : public ::testing::TestWithParam<std::tuple<std::string,                       // Input string
                                                 std::vector<std::vector<int16_t>>, // Expected result
                                                 bool                               // Should succeed
                                                 >> {};

TEST_P(ParserParameterizedTest, HandlesDifferentInputFormats) {
    // Arrange
    auto const & [input, expected, should_succeed] = GetParam();
    std::ofstream temp_file("param_test.txt");
    temp_file << input;
    temp_file.close();

    // Act
    auto result = parseInput("param_test.txt");

    // Assert
    EXPECT_EQ(result.has_value(), should_succeed);
    if (should_succeed) {
        EXPECT_THAT(*result, testing::ContainerEq(expected));
    }

    std::remove("param_test.txt");
}

INSTANTIATE_TEST_SUITE_P(ParserScenarios, ParserParameterizedTest,
                         ::testing::Values(
                             // Valid input with positive numbers
                             std::make_tuple("1,2\n3,4\n", std::vector<std::vector<int16_t>>{{1, 2}, {3, 4}}, true),
                             // Valid input with negative numbers
                             std::make_tuple("-1,2\n3,-4\n", std::vector<std::vector<int16_t>>{{-1, 2}, {3, -4}}, true),
                             // Empty input
                             std::make_tuple("", std::vector<std::vector<int16_t>>{}, true)));

TEST_F(ParserTest, HandlesInvalidNumberFormat) {
    // Arrange
    std::ofstream temp_file("invalid_test.txt");
    temp_file << invalid_input;
    temp_file.close();

    // Act
    auto result = parseInput("invalid_test.txt");

    // Assert
    ASSERT_FALSE(result.has_value());

    std::remove("invalid_test.txt");
}