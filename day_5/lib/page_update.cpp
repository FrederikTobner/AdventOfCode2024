
#include "page_update.hpp"

namespace aoc::day_5 {
std::optional<uint8_t> page_update::getMiddleElement() const {
    if (updateValues.empty()) {
        return std::nullopt;
    }
    return updateValues[updateValues.size() / 2];
}
} // namespace aoc::day_5