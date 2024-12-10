#pragma once

#include <vector>

namespace aoc::tree {

template <typename T> class tree_node {
  public:
    T value;
    std::vector<tree_node> children;

    tree_node(T value) : value(value) {
    }

    tree_node(T value, std::vector<tree_node> children) : value(value), children(children) {
    }

    auto addChild(tree_node child) -> void {
        children.push_back(child);
    }

    size_t countFullFillingCondition(auto condition) const {
        size_t count = condition(value) ? 1 : 0;
        for (auto const & child : children) {
            count += child.countFullFillingCondition(condition);
        }
        return count;
    }

    void executeOnFullFillingCondition(auto condition, auto action) const {
        if (condition(value)) {
            action(value);
        }
        for (auto & child : children) {
            child.executeOnFullFillingCondition(condition, action);
        }
    }
};

} // namespace aoc::tree