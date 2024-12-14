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

    auto executeIf(auto condition, auto action) const -> void {
        if (condition(value)) {
            action(value);
        }
        for (auto const & child : children) {
            child.executeIf(condition, action);
        }
    }
};

} // namespace aoc::tree