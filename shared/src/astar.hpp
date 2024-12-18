#pragma once

#pragma once

#include "direction.hpp"
#include "maze_cell.hpp"
#include "vector2d.hpp"

#include <cstdint>
#include <functional>
#include <vector>

namespace aoc::path_finding {

/// @brief A node in the maze
struct Node {
    /// @brief The position of the node
    aoc::math::vector_2d<int16_t> pos;

    /// @brief The direction the robot is facing
    aoc::math::Direction direction;

    /// @brief Equality operator
    /// @param other The other node to compare to
    /// @return True if the nodes are equal, false otherwise
    bool operator==(Node const & other) const;

    /// @brief Less than operator
    /// @param other The other node to compare to
    /// @return True if this node is less than the other node, false otherwise
    bool operator<(Node const & other) const;
};

/// @brief The result of the pathfinding
struct PathResult {
    std::vector<Node> path;
    int64_t cost;
};

/// @brief A maze solver
class MazeSolver {
  public:
    /// @brief Construct a new Maze Solver object
    /// @param maze The maze to solve
    MazeSolver(std::vector<std::vector<maze_cell>> const & maze, std::function<int(Node const &, Node const &)> fun);

    /// @brief Find the shortest path in the maze
    /// @return The shortest path in the maze
    auto findPath() -> PathResult;

    /// @brief Find all paths in the maze with the same cost as the cheapest path
    /// @return All paths in the maze with the same cost as the cheapest path
    auto findPaths() -> std::vector<PathResult>;

  private:
    /// @brief The maze to solve
    std::vector<std::vector<maze_cell>> m_maze;

    /// @brief The start node
    Node m_start;

    /// @brief The end node
    Node m_end;

    /// @brief Function pointer to calculate the cost for moving between two nodes
    std::function<int(Node const &, Node const &)> m_costFunction;

    /// @brief Check if a position is valid
    /// @param pos The position to check
    /// @return True if the position is valid, false otherwise
    auto isValid(aoc::math::vector_2d<int16_t> const & pos) const -> bool;

    /// @brief Finds the shortest path between two nodes
    /// @param start The start node
    /// @param end The end node
    /// @param heuristic The heuristic function to use
    /// @param getNeighbors The function to get the neighbors of a node
    /// @return The shortest path between the two nodes
    auto astar(Node start, Node end, std::function<int(Node const &, Node const &)> const & heuristic,
               std::function<std::vector<Node>(Node const &)> const & getNeighbors) -> PathResult;
};

} // namespace aoc::path_finding

namespace std {

/// @brief Hash specialization for the Node struct
template <> struct hash<aoc::path_finding::Node> {
    auto operator()(aoc::path_finding::Node const & n) const -> size_t {
        return hash<int16_t>{}(n.pos.x) ^ hash<int16_t>{}(n.pos.y) ^ hash<int>{}(static_cast<int>(n.direction));
    }
};
} // namespace std