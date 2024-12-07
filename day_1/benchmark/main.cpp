#include <benchmark/benchmark.h>

#include <cstdint>
#include <execution>
#include <set>
#include <string>

#include "../lib/calculations.hpp"

#include "../../shared/src/column_splitter.hpp"
#include "../../shared/src/parsing_rules.hpp"

static std::multiset<int64_t> createNewSet(size_t size) {
    std::multiset<int64_t> newSet;
    for (int i = 0; i < size; i++) {
        newSet.insert(rand() % size);
    }
    return newSet;
}

static void BM_CalulculateDistance(benchmark::State & state) {
    std::multiset<int64_t> leftList = createNewSet(1000000);
    std::multiset<int64_t> rightList = createNewSet(1000000);
    for (auto _ : state) {
        auto result = aoc::day_1::totalDistance(leftList, rightList);
    }
    state.SetItemsProcessed(state.iterations() * leftList.size());
}

BENCHMARK(BM_CalulculateDistance)
    ->Unit(benchmark::kMillisecond)
    ->UseRealTime()
    ->Threads(std::thread::hardware_concurrency())
    ->Iterations(100);

static void BM_CalulculateSimilarity(benchmark::State & state) {
    std::multiset<int64_t> leftList = createNewSet(10000);
    std::multiset<int64_t> rightList = createNewSet(10000);
    for (auto _ : state) {
        auto result = aoc::day_1::similarityScore(leftList, rightList);
    }
    state.SetItemsProcessed(state.iterations() * leftList.size());
}

BENCHMARK(BM_CalulculateSimilarity)
    ->Unit(benchmark::kMillisecond)
    ->UseRealTime()
    ->Threads(std::thread::hardware_concurrency())
    ->Iterations(100);

BENCHMARK_MAIN();