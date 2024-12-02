set(DAY 2)

add_subdirectory(src)
add_subdirectory(lib)

if(BUILD_TESTS)
    add_subdirectory(test)
endif()