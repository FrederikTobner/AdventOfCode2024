#pragma once

#include <cstdint>
#include <optional>
#include <vector>

namespace aoc::day_5 {
struct page_update {
    std::vector<uint8_t> updateValues;

    [[nodiscard]] std::optional<uint8_t> getMiddleElement() const {
        if (updateValues.empty()) {
            return std::nullopt;
        }
        return updateValues[updateValues.size() / 2];
    }
};
} // namespace aoc::day_5
