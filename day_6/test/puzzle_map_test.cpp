#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../lib/puzzle_map.hpp"

using namespace aoc::day_6;
using namespace testing;

class PuzzleMapTest : public Test {
  protected:
    static auto createTestMap(std::vector<std::vector<TileType>> layout, std::pair<size_t, size_t> guardPos)
        -> std::vector<std::vector<TileType>> {
        if (guardPos.first >= layout.size() || guardPos.second >= layout[0].size()) {
            throw std::invalid_argument("Guard position out of bounds");
        }
        if (layout[guardPos.first][guardPos.second] != TileType::Empty) {
            throw std::invalid_argument("Guard position must be on empty tile");
        }
        layout[guardPos.first][guardPos.second] = TileType::Guard;
        return layout;
    }
};

TEST_F(PuzzleMapTest, GuardMovesForwardUntilBlocked) {
    auto const map = createTestMap(
        {
            {TileType::Empty, TileType::Empty, TileType::Empty},
            {TileType::Empty, TileType::Empty, TileType::Obstacle},
            {TileType::Empty, TileType::Empty, TileType::Empty},
        },
        {1, 0});

    PuzzleMap puzzle(map, {1, 0}, FacingDirection::Right);
    EXPECT_TRUE(puzzle.update()); // Move to (1,1)
    puzzle.update();              // Hit obstacle at (1,2) - turn around
    EXPECT_TRUE(puzzle.update()); // Move to (1,0)
    auto positions = puzzle.getVisitedPositions();
    EXPECT_THAT(positions, UnorderedElementsAre(VisitedPosition{1, 0, FacingDirection::Right},
                                                VisitedPosition{1, 1, FacingDirection::Right},
                                                VisitedPosition{1, 1, FacingDirection::Down}));
}

TEST_F(PuzzleMapTest, GuardTurnsRightWhenBlocked) {
    auto const map = createTestMap(
        {
            {TileType::Empty, TileType::Empty, TileType::Empty},
            {TileType::Empty, TileType::Empty, TileType::Obstacle},
            {TileType::Empty, TileType::Empty, TileType::Empty},
        },
        {1, 1});

    PuzzleMap puzzle(map, {1, 1}, FacingDirection::Right);
    puzzle.update();
    puzzle.update();

    auto positions = puzzle.getVisitedPositions();
    EXPECT_THAT(positions, UnorderedElementsAre(VisitedPosition{1, 1, FacingDirection::Right},
                                                VisitedPosition{1, 1, FacingDirection::Down}));
}

TEST_F(PuzzleMapTest, DetectsOutOfBounds) {
    auto const map = createTestMap(
        {
            {TileType::Empty, TileType::Empty, TileType::Empty},
            {TileType::Empty, TileType::Empty, TileType::Empty},
        },
        {0, 1});

    PuzzleMap puzzle(map, {0, 1}, FacingDirection::Up);
    puzzle.update();
    EXPECT_TRUE(puzzle.isGuardOutOfBounds());
}

TEST_F(PuzzleMapTest, TracksVisitedPositions) {
    auto map = createTestMap(
        {
            {TileType::Empty, TileType::Empty, TileType::Empty},
            {TileType::Empty, TileType::Empty, TileType::Empty},
        },
        {0, 0});

    PuzzleMap puzzle(map, {0, 0}, FacingDirection::Right);
    puzzle.update();
    puzzle.update();

    auto positions = puzzle.getVisitedPositions();
    EXPECT_THAT(positions, SizeIs(2)); // Start position + new position
}