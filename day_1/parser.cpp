
#include "parser.hpp"
#include <ranges>
#include <string>

auto parseLine(std::string_view line) -> std::pair<int64_t, int64_t> 
{
    auto numbers = line 
        | std::views::split(' ')
        | std::views::filter([](auto&& rng) { return !std::string_view(rng).empty(); })
        | std::views::transform([](auto&& rng) { 
            return std::stoll(std::string(rng.begin(), rng.end())); 
        });
    
    auto it = numbers.begin();
    auto first = *it++;
    auto second = *it;
    return {first, second};
}

auto parseInput(std::string_view input) -> std::pair<std::multiset<int64_t>, std::multiset<int64_t>> 
{
    std::multiset<int64_t> set1, set2;
    
    auto lines = input | std::views::split('\n')
                      | std::views::transform([](auto&& rng) { 
                          return std::string_view(rng.begin(), rng.end()); 
                      })
                      | std::views::filter([](auto sv) { return !sv.empty(); });

    for (const auto& line : lines) {
        auto [a, b] = parseLine(line);
        set1.insert(a);
        set2.insert(b);
    }
    
    return {set1, set2};
}