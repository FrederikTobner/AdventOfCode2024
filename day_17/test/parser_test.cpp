#include "../lib/parser.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../lib/opcode.hpp"

using namespace aoc::day_17;
using namespace testing;

class ParserTest : public Test {
  protected:
    void SetUp() override {
    }
};

TEST_F(ParserTest, ValidInputParsesCorrectly) {
    // Arrange
    auto const input = "RegisterA: 1\nRegisterB: 2\nRegisterC: 3\n\nOpcode:1,2,3,4";

    // Act
    auto result = parse_program(input);

    // Assert
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->register_a, 1);
    EXPECT_EQ(result->register_b, 2);
    EXPECT_EQ(result->register_c, 3);
    ASSERT_THAT(result->m_chunk.m_data,
                ElementsAre(static_cast<aoc::day_17::opcode>(1), static_cast<aoc::day_17::opcode>(2),
                            static_cast<aoc::day_17::opcode>(3), static_cast<aoc::day_17::opcode>(4)));
}

TEST_F(ParserTest, InvalidRegisterInputReturnsError) {
    // Arrange
    auto const input = "RegisterA: invalid\nRegisterB: 2\nRegisterC: 3\n\nOpcode:1,2,3,4";

    // Act
    auto result = parse_program(input);

    // Assert
    ASSERT_FALSE(result.has_value());
}

class ParserParameterizedTest : public TestWithParam<std::tuple<std::string, std::array<int64_t, 3>>> {};

TEST_P(ParserParameterizedTest, RegisterParsing) {
    // Arrange
    auto const [input, expected_registers] = GetParam();
    auto const opcodes = "\n\nOpcode:1";
    auto const full_input = input + opcodes;

    // Act
    auto result = parse_program(full_input);

    // Assert
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->register_a, std::get<0>(expected_registers));
    EXPECT_EQ(result->register_b, std::get<1>(expected_registers));
    EXPECT_EQ(result->register_c, std::get<2>(expected_registers));
}

INSTANTIATE_TEST_SUITE_P(
    RegisterValues, ParserParameterizedTest,
    Values(std::make_tuple("RegisterA: 1\nRegisterB: 2\nRegisterC: 3", std::array<int64_t, 3>{1, 2, 3}),
           std::make_tuple("RegisterA: -1\nRegisterB: 0\nRegisterC: 100", std::array<int64_t, 3>{-1, 0, 100}),
           std::make_tuple("RegisterA: 0\nRegisterB: 0\nRegisterC: 0", std::array<int64_t, 3>{0, 0, 0})));

TEST_F(ParserTest, MissingDelimiterReturnsError) {
    // Arrange
    auto const input = "RegisterA: 1\nRegisterB: 2\nRegisterC: 3Opcode:1,2,3,4";

    // Act
    auto result = parse_program(input);

    // Assert
    ASSERT_FALSE(result.has_value());
}

TEST_F(ParserTest, InvalidOpcodeFormatReturnsError) {
    // Arrange
    auto const input = "RegisterA: 1\nRegisterB: 2\nRegisterC: 3\n\nOpcode:invalid,2,3,4";

    //  Act & Assert
    ASSERT_THROW(auto res = parse_program(input), std::invalid_argument);
}