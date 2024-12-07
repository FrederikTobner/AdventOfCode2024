#include <benchmark/benchmark.h>

#include <cstdint>
#include <execution>
#include <set>
#include <string>

#include "../src/column_splitter.hpp"
#include "../src/parsing_rules.hpp"

static std::string createInput(size_t size) {
    std::string input;
    for (int i = 0; i < size; i++) {
        input += std::to_string(rand() % size) + " " + std::to_string(rand() % size) + "\n";
    }
    return input;
}

static void BM_ParseLinesInSequence(benchmark::State & state) {
    auto input = createInput(20000);
    volatile size_t size = input.size();

    for (auto _ : state) {
        auto result = aoc::splitter::columnbased::split<int64_t, 2, std::multiset>(
            input, aoc::parser::rules::parse_number<int64_t>, std::execution::seq);
        // benchmark::DoNotOptimize(result);
    }

    state.SetItemsProcessed(state.iterations() * input.size());
}

BENCHMARK(BM_ParseLinesInSequence)
    ->Unit(benchmark::kMillisecond)
    ->Threads(std::thread::hardware_concurrency())
    ->Iterations(1);

static void BM_ParseLinesInParrallel(benchmark::State & state) {
    auto input = createInput(2000);

    for (auto _ : state) {
        auto result = aoc::splitter::columnbased::split<int64_t, 2>(input, aoc::parser::rules::parse_number<int64_t>,
                                                                    std::execution::par);
        // benchmark::DoNotOptimize(result);
    }

    state.SetItemsProcessed(state.iterations() * input.size());
}

BENCHMARK(BM_ParseLinesInParrallel)
    ->Unit(benchmark::kMillisecond)
    ->UseRealTime()
    ->Threads(std::thread::hardware_concurrency())
    ->Iterations(1);

BENCHMARK_MAIN();