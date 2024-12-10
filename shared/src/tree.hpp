#pragma once

#include <vector>

namespace aoc::tree {

template <typename T> class Node {
  public:
    T value;
    std::vector<Node> children;

    Node(T value) : value(value) {
    }

    auto addChild(Node child) -> void {
        children.push_back(child);
    }

    size_t countFullFillingCondition(auto condition) const {
        size_t count = condition(value) ? 1 : 0;
        for (auto const & child : children) {
            count += child.countFullFillingCondition(condition);
        }
        return count;
    }

    void executeOnFullFillingCondition(auto condition, auto action) {
        if (condition(value)) {
            action(value);
        }
        for (auto & child : children) {
            child.executeOnFullFillingCondition(condition, action);
        }
    }
};

} // namespace aoc::tree