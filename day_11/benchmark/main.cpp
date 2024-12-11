#include <benchmark/benchmark.h>

#include <cstddef>
#include <thread>
#include <vector>


#include "../lib/stone.hpp"

static void BM_CalculateStones(benchmark::State & state) {
    std::vector<size_t> stones;
    for (int i = 0; i < 10; i++) {
        stones.push_back(rand() % 1000);
    }
    for (auto _ : state) {
        auto result = aoc::day_11::calculateStones(stones, 100);
    }
    state.SetItemsProcessed(state.iterations() * stones.size());
}

BENCHMARK(BM_CalculateStones)
    ->Unit(benchmark::kMillisecond)
    ->UseRealTime()
    ->Threads(std::thread::hardware_concurrency())
    ->Iterations(100);

BENCHMARK_MAIN();