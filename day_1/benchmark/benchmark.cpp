#include <benchmark/benchmark.h>

#include "../lib/calculations.hpp"
#include "../lib/parser.hpp"

static std::string createInput(size_t size) {
    std::string input;
    for (int i = 0; i < size; i++) {
        input += std::to_string(rand() % 1000) + " " + std::to_string(rand() % 1000) + "\n";
    }
    return input;
}

static std::multiset<int64_t> createNewSet(size_t size) {
    // I need a way more entries to make this benchmark meaningful - generating 1000 entries
    std::multiset<int64_t> newSet;
    for (int i = 0; i < size; i++) {
        // Insert a random number between 0 and 1000
        newSet.insert(rand() % 1000);
    }
    return newSet;
}

static void BM_CalulculateDistanceParrallel(benchmark::State & state) {
    for (auto _ : state) {

        std::multiset<int64_t> leftList = createNewSet(1000);
        std::multiset<int64_t> rightList = createNewSet(1000);

        auto result = calculateTotalDistance(leftList, rightList);
    }
}
// Register the function as a benchmark
BENCHMARK(BM_CalulculateDistanceParrallel);

static void BM_CalulculateDistanceSequential(benchmark::State & state) {
    for (auto _ : state) {

        std::multiset<int64_t> leftList = createNewSet(1000);
        std::multiset<int64_t> rightList = createNewSet(1000);

        auto result = calculateTotalDistance(leftList, rightList, CalcProcessingMode::Sequential);
    }
}

BENCHMARK(BM_CalulculateDistanceSequential);

static void BM_CalulculateSimilarityParallel(benchmark::State & state) {
    for (auto _ : state) {

        std::multiset<int64_t> leftList = createNewSet(1000);
        std::multiset<int64_t> rightList = createNewSet(1000);

        auto result = calculateSimilarityScore(leftList, rightList);
    }
}
// Register the function as a benchmark
BENCHMARK(BM_CalulculateSimilarityParallel);

static void BM_CalulculateSimilaritySequential(benchmark::State & state) {
    for (auto _ : state) {

        std::multiset<int64_t> leftList = createNewSet(1000);
        std::multiset<int64_t> rightList = createNewSet(1000);

        auto result = calculateSimilarityScore(leftList, rightList, CalcProcessingMode::Sequential);
    }
}

BENCHMARK(BM_CalulculateDistanceSequential);

static void BM_ParseLinesInParrallel(benchmark::State & state) {
    for (auto _ : state) {
        auto result = parseInput(createInput(1000), parser::ProcessingMode::Parallel);
    }
}

BENCHMARK(BM_ParseLinesInParrallel);

static void BM_ParseLinesInSequence(benchmark::State & state) {
    for (auto _ : state) {
        auto result = parseInput(createInput(1000), parser::ProcessingMode::Sequential);
    }
}

BENCHMARK(BM_ParseLinesInSequence);

BENCHMARK_MAIN();