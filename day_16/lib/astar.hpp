#pragma once

#pragma once

#include "../../shared/src/direction.hpp"
#include "../../shared/src/vector2d.hpp"

#include <cstdint>
#include <functional>
#include <queue>
#include <ranges>
#include <unordered_map>
#include <vector>

#include "maze_cell.hpp"

namespace aoc::day_16 {

struct Node {
    aoc::math::vector_2d<int16_t> pos;
    aoc::math::Direction direction;
    bool operator==(Node const & other) const {
        return pos == other.pos && direction == other.direction;
    }

    bool operator<(Node const & other) const {
        if (pos.y != other.pos.y) {
            return pos.y < other.pos.y;
        }
        if (pos.x != other.pos.x) {
            return pos.x < other.pos.x;
        }
        return static_cast<int>(direction) < static_cast<int>(other.direction);
    }
};
} // namespace aoc::day_16

namespace std {
template <> struct hash<aoc::day_16::Node> {
    auto operator()(aoc::day_16::Node const & n) const -> size_t {
        return hash<int16_t>{}(n.pos.x) ^ hash<int16_t>{}(n.pos.y) ^ hash<int>{}(static_cast<int>(n.direction));
    }
};
} // namespace std

namespace aoc::day_16 {

struct PathResult {
    std::vector<Node> path;
    int cost;
};

class MazeSolver {
  public:
    MazeSolver(std::vector<std::vector<maze_cell>> const & maze) : m_maze(maze) {
        for (size_t y = 0; y < maze.size(); ++y) {
            for (size_t x = 0; x < maze[y].size(); ++x) {
                if (maze[y][x] == maze_cell::start) {
                    m_start = {aoc::math::vector_2d<int16_t>{static_cast<int16_t>(x), static_cast<int16_t>(y)},
                               aoc::math::Direction::RIGHT};
                } else if (maze[y][x] == maze_cell::end) {
                    m_end = {aoc::math::vector_2d<int16_t>{static_cast<int16_t>(x), static_cast<int16_t>(y)},
                             aoc::math::Direction::UP};
                }
            }
        }
    }

    auto findPath() -> PathResult {
        auto heuristic = [](Node const & a, Node const & b) {
            return std::abs(a.pos.x - b.pos.x) + std::abs(a.pos.y - b.pos.y);
        };

        auto getNeighbors = [this](Node const & n) {
            std::vector<Node> neighbors;
            for (auto const & dir : {aoc::math::Direction::UP, aoc::math::Direction::RIGHT, aoc::math::Direction::DOWN,
                                     aoc::math::Direction::LEFT}) {
                auto vec = aoc::math::getDirectionVector(dir);
                auto new_pos = n.pos + vec;
                if (isValid(new_pos)) {
                    neighbors.push_back({new_pos, dir});
                }
            }
            return neighbors;
        };

        auto result = astar(m_start, m_end, heuristic, getNeighbors);
        return result;
    }

    // Finds the paths with the lowest cost from the start to the end
    auto findPaths() -> std::vector<PathResult> {

        // First find the shortest path - then block it one step at a time and find the next shortest path
        // Compare the cost of the next shortest path with the previous shortest path
        // If the cost is the same, add the path to the list of shortest paths
        // If the cost is different, stop and return the list of shortest paths

        std::vector<PathResult> allPaths;
        auto heuristic = [](Node const & a, Node const & b) {
            return std::abs(a.pos.x - b.pos.x) + std::abs(a.pos.y - b.pos.y);
        };

        auto getNeighbors = [this](Node const & n) {
            std::vector<Node> neighbors;
            for (auto const & dir : {aoc::math::Direction::UP, aoc::math::Direction::RIGHT, aoc::math::Direction::DOWN,
                                     aoc::math::Direction::LEFT}) {
                auto vec = aoc::math::getDirectionVector(dir);
                auto new_pos = n.pos + vec;
                if (isValid(new_pos)) {
                    neighbors.push_back({new_pos, dir});
                }
            }
            return neighbors;
        };

        auto shortest_found = astar(m_start, m_end, heuristic, getNeighbors);
        if (shortest_found.cost == -1) {
            return allPaths;
        }

        for (auto const & node : shortest_found.path) {
            m_maze[node.pos.y][node.pos.x] = maze_cell::wall;
            // Look for shortest path again
            auto result = astar(m_start, m_end, heuristic, getNeighbors);
            if (result.cost == shortest_found.cost) {
                allPaths.push_back(result);
            }
            m_maze[node.pos.y][node.pos.x] = maze_cell::empty;
        }
        return allPaths;
    }

  private:
    std::vector<std::vector<maze_cell>> m_maze;
    Node m_start;
    Node m_end;

    auto isValid(aoc::math::vector_2d<int16_t> const & pos) const -> bool {
        return pos.y >= 0 && pos.y < m_maze.size() && pos.x >= 0 && pos.x < m_maze[0].size() &&
               m_maze[pos.y][pos.x] != maze_cell::wall;
    }

    auto astar(Node start, Node end, std::function<int(Node const &, Node const &)> const & heuristic,
               std::function<std::vector<Node>(Node const &)> const & getNeighbors) -> PathResult {
        std::vector<Node> path;
        std::unordered_map<Node, Node> cameFrom;
        std::unordered_map<Node, int> costSoFar;

        auto cmp = [&end, &heuristic, &costSoFar](Node const & a, Node const & b) {
            int f1 = costSoFar[a] + heuristic(a, end);
            int f2 = costSoFar[b] + heuristic(b, end);
            return f1 > f2 || (f1 == f2 && a < b); // Add tiebreaker
        };

        std::priority_queue<Node, std::vector<Node>, decltype(cmp)> frontier(cmp);
        frontier.push(start);

        cameFrom[start] = start;
        costSoFar[start] = 0;
        bool found = false;

        while (!frontier.empty()) {
            auto current = frontier.top();
            frontier.pop();

            if (current == end) {
                found = true;
                break;
            }

            for (auto const & next : getNeighbors(current)) {
                auto newCost = costSoFar[current] + (current.direction == next.direction ? 1 : 1001);
                if (!costSoFar.contains(next) || newCost < costSoFar[next]) {
                    costSoFar[next] = newCost;
                    int priority = newCost + heuristic(next, end);
                    frontier.push(next);
                    cameFrom[next] = current;
                }
            }
        }

        if (!found) {
            return PathResult{std::vector<Node>{}, -1};
        }
        Node current = end;
        while (current != start) {
            path.push_back(current);
            current = cameFrom[current];
        }
        path.push_back(start);
        std::ranges::reverse(path);

        return PathResult{path, costSoFar[end]};
    }
};

} // namespace aoc::day_16