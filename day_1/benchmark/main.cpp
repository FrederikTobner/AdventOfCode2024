#include <benchmark/benchmark.h>
#include <iostream>

#include "../lib/calculations.hpp"
#include "../lib/parser.hpp"

static std::string createInput(size_t size) {
    std::string input;
    for (int i = 0; i < size; i++) {
        input += std::to_string(rand() % size) + " " + std::to_string(rand() % size) + "\n";
    }
    return input;
}

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
        auto result = calculations::totalDistance(leftList, rightList);
    }
    state.SetItemsProcessed(state.iterations() * leftList.size());
}

BENCHMARK(BM_CalulculateDistance)
    ->Unit(benchmark::kMillisecond)
    ->UseRealTime()
    ->Threads(std::thread::hardware_concurrency())
    ->Iterations(10);

static void BM_CalulculateSimilarity(benchmark::State & state) {
    std::multiset<int64_t> leftList = createNewSet(10000);
    std::multiset<int64_t> rightList = createNewSet(10000);
    for (auto _ : state) {
        auto result = calculations::similarityScore(leftList, rightList);
    }
    state.SetItemsProcessed(state.iterations() * leftList.size());
}

BENCHMARK(BM_CalulculateSimilarity)
    ->Unit(benchmark::kMillisecond)
    ->UseRealTime()
    ->Threads(std::thread::hardware_concurrency())
    ->Iterations(20);

static void BM_ParseLinesInParrallel(benchmark::State & state) {
    auto input = createInput(30000);

    for (auto _ : state) {
        state.PauseTiming();
        auto result = parseInput(input, parser::ProcessingMode::Parallel);
        state.ResumeTiming();

        benchmark::DoNotOptimize(result);
        benchmark::ClobberMemory();
    }

    state.SetItemsProcessed(state.iterations() * input.size());
}

BENCHMARK(BM_ParseLinesInParrallel)
    ->Unit(benchmark::kMillisecond)
    ->UseRealTime()
    ->Threads(std::thread::hardware_concurrency())
    ->Iterations(1);

static void BM_ParseLinesInSequence(benchmark::State & state) {
    auto input = createInput(30000);
    volatile size_t size = input.size();

    for (auto _ : state) {
        state.PauseTiming();
        auto result = parseInput(input, parser::ProcessingMode::Sequential);
        state.ResumeTiming();
        if (!result) {
            state.SkipWithError("Parser error occurred");
            break;
        }
        benchmark::DoNotOptimize(result);
        benchmark::ClobberMemory();
    }

    state.SetItemsProcessed(state.iterations() * input.size());
}

BENCHMARK(BM_ParseLinesInSequence)
    ->Unit(benchmark::kMillisecond)
    ->Threads(std::thread::hardware_concurrency())
    ->Iterations(1);

BENCHMARK_MAIN();