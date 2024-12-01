file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(${PROJECT_NAME}_day_1 ${SOURCES})

# Set C++23 standard and compiler-specific flags
if(MSVC)
    target_compile_options(${PROJECT_NAME}_day_1 PRIVATE /std:c++latest)
else()
    target_compile_features(${PROJECT_NAME}_day_1 PRIVATE cxx_std_23)
    target_compile_options(${PROJECT_NAME}_day_1 PRIVATE
        -std=c++23
        -D_GLIBCXX_USE_CXX11_ABI=1
        -D_GLIBCXX_ASSERTIONS
    )
    # Add definition to enable experimental features
    target_compile_definitions(${PROJECT_NAME}_day_1 PRIVATE
        _GLIBCXX_EXPERIMENTAL_ENABLED=1
    )
endif()

configure_file(input.txt input.txt COPYONLY)