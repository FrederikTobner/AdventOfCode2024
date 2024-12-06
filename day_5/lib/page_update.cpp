
#include "page_update.hpp"

namespace aoc::day_5 {
uint8_t page_update::getMiddleElement() const {
    return updateValues[updateValues.size() / 2];
}
auto page_update::cbegin() const -> std::vector<uint8_t>::const_iterator {
    return updateValues.cbegin();
}
} // namespace aoc::day_5