#include "astar.hpp"

#include <algorithm>
#include <queue>
#include <ranges>
#include <unordered_map>

namespace aoc::path_finding {

bool Node::operator==(Node const & other) const {
    return pos == other.pos && direction == other.direction;
}

bool Node::operator<(Node const & other) const {
    if (pos.y != other.pos.y) {
        return pos.y < other.pos.y;
    }
    if (pos.x != other.pos.x) {
        return pos.x < other.pos.x;
    }
    return static_cast<int>(direction) < static_cast<int>(other.direction);
}

MazeSolver::MazeSolver(std::vector<std::vector<maze_cell>> const & maze,
                       std::function<int(Node const &, Node const &)> fun)
    : m_maze(maze), m_costFunction(fun) {
    for (size_t y = 0; y < maze.size(); ++y) {
        for (size_t x = 0; x < maze[y].size(); ++x) {
            if (maze[y][x] == maze_cell::START) {
                m_start = {aoc::math::vector_2d<int16_t>{static_cast<int16_t>(x), static_cast<int16_t>(y)},
                           aoc::math::Direction::RIGHT};
            } else if (maze[y][x] == maze_cell::END) {
                m_end = {aoc::math::vector_2d<int16_t>{static_cast<int16_t>(x), static_cast<int16_t>(y)},
                         aoc::math::Direction::UP};
            }
        }
    }
}

/// @brief Find the shortest path in the maze
/// @return The shortest path in the maze
auto MazeSolver::findPath() -> PathResult {
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

/// @brief Find all paths in the maze with the same cost as the cheapest path
/// @return All paths in the maze with the same cost as the cheapest path
auto MazeSolver::findPaths() -> std::vector<PathResult> {
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
        m_maze[node.pos.y][node.pos.x] = maze_cell::WALL;
        // Look for shortest path again
        auto result = astar(m_start, m_end, heuristic, getNeighbors);
        if (result.cost == shortest_found.cost) {
            allPaths.push_back(result);
        }
        m_maze[node.pos.y][node.pos.x] = maze_cell::EMPTY;
    }
    return allPaths;
}

auto MazeSolver::isValid(aoc::math::vector_2d<int16_t> const & pos) const -> bool {
    return pos.y >= 0 && pos.y < m_maze.size() && pos.x >= 0 && pos.x < m_maze[0].size() &&
           m_maze[pos.y][pos.x] != maze_cell::WALL;
}

auto MazeSolver::astar(Node start, Node end, std::function<int(Node const &, Node const &)> const & heuristic,
                       std::function<std::vector<Node>(Node const &)> const & getNeighbors) -> PathResult {
    std::vector<Node> path;
    std::unordered_map<Node, Node> cameFrom;
    std::unordered_map<Node, int64_t> costSoFar;

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
    aoc::math::Direction lastDirection = start.direction;

    while (!frontier.empty()) {
        auto current = frontier.top();
        frontier.pop();

        if (current.pos == end.pos) {
            found = true;
            lastDirection = current.direction;
            break;
        }

        for (auto const & next : getNeighbors(current)) {
            auto newCost = costSoFar[current] + m_costFunction(current, next);
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
    Node current_node = Node{end.pos, lastDirection};
    while (current_node.pos != start.pos) {
        path.push_back(current_node);
        current_node = cameFrom[current_node];
    }
    path.push_back(start);
    std::ranges::reverse(path);

    return PathResult{path, costSoFar[Node{end.pos, lastDirection}]};
}

} // namespace aoc::path_finding