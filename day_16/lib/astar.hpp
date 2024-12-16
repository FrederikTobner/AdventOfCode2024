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
    MazeSolver(std::vector<std::vector<maze_cell>> const & maze) : maze_(maze) {
        for (size_t y = 0; y < maze.size(); ++y) {
            for (size_t x = 0; x < maze[y].size(); ++x) {
                if (maze[y][x] == maze_cell::start) {
                    start_ = {aoc::math::vector_2d<int16_t>{static_cast<int16_t>(x), static_cast<int16_t>(y)},
                              aoc::math::Direction::RIGHT};
                } else if (maze[y][x] == maze_cell::end) {
                    end_ = {aoc::math::vector_2d<int16_t>{static_cast<int16_t>(x), static_cast<int16_t>(y)},
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

        auto result = astar(start_, end_, heuristic, getNeighbors);
        return result;
    }

  private:
    std::vector<std::vector<maze_cell>> maze_;
    Node start_;
    Node end_;

    bool isValid(aoc::math::vector_2d<int16_t> const & pos) const {
        return pos.y >= 0 && pos.y < maze_.size() && pos.x >= 0 && pos.x < maze_[0].size() &&
               maze_[pos.y][pos.x] != maze_cell::wall;
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