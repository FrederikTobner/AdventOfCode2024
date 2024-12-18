#include "../lib/transpiler.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace aoc::day_17;
using namespace testing;

class TranspilerTest : public Test {
  protected:
    void SetUp() override {
    }
};

TEST_F(TranspilerTest, EmptyProgramTranspilesCorrectly) {
    // Arrange
    program test_program{.m_chunk = chunk{}, .register_a = 0, .register_b = 0, .register_c = 0};

    // Act
    auto result = transpile(test_program);

    // Assert
    EXPECT_THAT(result, HasSubstr("int64_t a = 0"));
    EXPECT_THAT(result, HasSubstr("int64_t b = 0"));
    EXPECT_THAT(result, HasSubstr("int64_t c = 0"));
    EXPECT_THAT(result, HasSubstr("#include <cmath>"));
}

TEST_F(TranspilerTest, BasicOperationsTranspileCorrectly) {
    // Arrange
    program test_program{
        .m_chunk = chunk{{opcode::ADV, opcode::BXL}}, .register_a = 1, .register_b = 2, .register_c = 3};

    // Act
    auto result = transpile(test_program);

    // Assert
    EXPECT_THAT(result, HasSubstr("a = a / "));
}

TEST_F(TranspilerTest, ComplexProgramGeneratesLabels) {
    // Arrange
    program test_program{
        .m_chunk = chunk{{opcode::JNZ, opcode::OUT, opcode::BXL}}, .register_a = 1, .register_b = 0, .register_c = 0};

    // Act
    auto result = transpile(test_program);

    // Assert
    EXPECT_THAT(result, HasSubstr("_0:"));
    EXPECT_THAT(result, HasSubstr("goto _"));
}

class TranspilerParameterizedTest : public TestWithParam<std::tuple<std::vector<opcode>, std::vector<std::string>>> {};

TEST_P(TranspilerParameterizedTest, OpcodeTranslation) {
    // Arrange
    auto const [opcodes, expected_snippets] = GetParam();
    program test_program{.m_chunk = chunk{opcodes}, .register_a = 0, .register_b = 0, .register_c = 0};

    // Act
    auto result = transpile(test_program);

    // Assert
    for (auto const & snippet : expected_snippets) {
        EXPECT_THAT(result, HasSubstr(snippet));
    }
}

INSTANTIATE_TEST_SUITE_P(OpcodeTranslations, TranspilerParameterizedTest,
                         Values(std::make_tuple(std::vector<opcode>{opcode::ADV, opcode::BXL},
                                                std::vector<std::string>{"a = a /"}),
                                std::make_tuple(std::vector<opcode>{opcode::OUT, opcode::BST},
                                                std::vector<std::string>{"std::cout", "b ="})));

TEST_F(TranspilerTest, ExtractHelpersGeneratesValidFunction) {
    // Arrange
    chunk test_chunk{{opcode::ADV, opcode::BXL, opcode::BST}};

    // Act
    auto result = extract_helpers(test_chunk);

    // Assert
    EXPECT_THAT(result, HasSubstr("auto calculate_byte(int64_t a)"));
    EXPECT_THAT(result, HasSubstr("find_register_value"));
    EXPECT_THAT(result, HasSubstr("#include <cmath>"));
}

TEST_F(TranspilerTest, OutputOperationFormatsCorrectly) {
    // Arrange
    program test_program{.m_chunk = chunk{{opcode::OUT}}, .register_a = 0, .register_b = 0, .register_c = 0};

    // Act
    auto result = transpile(test_program);

    // Assert
    EXPECT_THAT(result, HasSubstr("first_out"));
    EXPECT_THAT(result, HasSubstr("std::cout"));
    EXPECT_THAT(result, HasSubstr("std::endl"));
}