file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(${PROJECT_NAME}_day_1 ${SOURCES})

# Set C++23 standard and compiler-specific flags
if(MSVC)
    target_compile_options(${PROJECT_NAME}_day_1 PRIVATE /std:c++latest)
endif()

configure_file(input.txt input.txt COPYONLY)