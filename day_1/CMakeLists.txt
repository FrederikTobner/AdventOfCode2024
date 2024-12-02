set(DAY 1)

add_subdirectory(src)
add_subdirectory(lib)

if(TRUE)
    add_subdirectory(test)
endif()
if(BUILD_BENCHMARKS)
    add_subdirectory(benchmark)
endif()