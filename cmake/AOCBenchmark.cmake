macro(aoc_add_benchmark)
    file(GLOB_RECURSE BENCHMARK_TESTS_SOURCES *.cpp)    
    if(NOT BENCHMARK_TESTS_SOURCES)
        return()
    endif()
    set(PERFORMANCE_TESTS_EXE_NAME ${PROJECT_NAME}_day_${DAY}_performance_tests)
    add_executable(${PERFORMANCE_TESTS_EXE_NAME} ${BENCHMARK_TESTS_SOURCES})
    include(AddDependency)
    add_github_dependency_by_tag(googletest google/googletest v1.15.2)
    add_github_dependency_by_tag(benchmark google/benchmark v1.9.1)
    target_link_libraries(${PERFORMANCE_TESTS_EXE_NAME} ${PROJECT_NAME}_day_${DAY}_lib benchmark::benchmark)
endmacro()