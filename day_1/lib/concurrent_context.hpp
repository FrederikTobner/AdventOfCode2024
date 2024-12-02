/**
 * @file concurrent_context.hpp
 * @brief Thread-safe value container
 * @details Provides a thread-safe mechanism for storing and retrieving a single value.
 */

#pragma once

#include <atomic>
#include <mutex>
#include <system_error>

namespace threads {

/**
 * @brief Thread-safe value container
 * @details Provides a thread-safe mechanism for storing and retrieving a single value.
 * @tparam T The value type to store (default: std::error_code)
 */
template <typename T = std::error_code> class concurrent_context {
  public:
    /**
     * @brief Sets the first encountered value
     * @param value Value to set if no previous value exists
     */
    void setValue(T value);

    /**
     * @brief Checks if an value was recorded
     * @return true if an value was recorded, false otherwise
     */
    [[nodiscard]] bool hasValue() const noexcept;

    /**
     * @brief Retrieves the first value recorded
     * @return The stored value
     */
    [[nodiscard]] T getValue() const noexcept;

  private:
    std::atomic<bool> has_value{false};
    mutable std::mutex context_mutex;
    T value;
};

template <typename T> void concurrent_context<T>::setValue(T value) {
    if (!has_value.exchange(true, std::memory_order_relaxed)) {
        std::scoped_lock lock(context_mutex);
        value = std::move(value);
    }
}

template <typename T> bool concurrent_context<T>::hasValue() const noexcept {
    return has_value.load(std::memory_order_relaxed);
}

template <typename T> T concurrent_context<T>::getValue() const noexcept {
    std::scoped_lock lock(context_mutex);
    return value;
}

} // namespace threads