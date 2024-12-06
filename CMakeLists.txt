cmake_minimum_required(VERSION 3.24)
project(AdventofCode2024 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the external cmake files from my github repository
include(FetchContent)
FetchContent_Declare(
  ExternalCMakeFiles
  GIT_REPOSITORY https://github.com/FrederikTobner/CMakeLib.git
  GIT_TAG main
  SOURCE_DIR ${CMAKE_BINARY_DIR}/external/ExternalCMakeFiles/src
)
FetchContent_MakeAvailable(ExternalCMakeFiles)
list(APPEND CMAKE_MODULE_PATH 
"${CMAKE_BINARY_DIR}/external/ExternalCMakeFiles/src" 
"${CMAKE_SOURCE_DIR}/cmake")

include(Options)
add_option(BUILD_SOLUTIONS "Build AOC solutions" ON)
add_option(BUILD_TESTS "Build tests" OFF)
add_option(BUILD_BENCHMARKS "Build benchmarks" OFF)

if(BUILD_TESTS)
    enable_testing()
endif()

include(AOCBenchmark)
include(AOCExecutable)
include(AOCLibrary)
include(AOCTest)
include(AOCDay)

add_subdirectory(shared)

foreach(day RANGE 1 24)
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/day_${day})
        add_subdirectory(day_${day})
    endif()
endforeach()
