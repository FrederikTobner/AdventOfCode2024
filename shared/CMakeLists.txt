add_subdirectory(src)
if(BUILD_TESTS)
    add_subdirectory(test)
endif()
if(BUILD_BENCHMARKS)
    add_subdirectory(benchmark)
endif()