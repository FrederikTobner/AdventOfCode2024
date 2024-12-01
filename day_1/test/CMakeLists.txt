set(TESTS_EXE_NAME ${PROJECT_NAME}_day_${DAY}_tests)

# Used to add dependencies to the project
include(AddDependency)

# Fetches google-test framework from the github repo
add_github_dependency_by_tag(googletest google/googletest v1.14.0)

file(GLOB_RECURSE TEST_SOURCES *.cpp)

# Builds tests
add_executable(${TESTS_EXE_NAME} ${TEST_SOURCES})

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

#Links googletest and googlemock to the test executable
target_link_libraries(${TESTS_EXE_NAME} GTest::gtest_main GTest::gmock_main ${PROJECT_NAME}_day_${DAY}_lib)

# Add GoogleTest Cmake scripts
include(GoogleTest)

# Discovers all testcases in the project and creates a main method
gtest_discover_tests(${TESTS_EXE_NAME})