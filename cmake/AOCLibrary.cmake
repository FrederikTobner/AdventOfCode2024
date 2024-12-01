macro(aoc_add_library)
    file(GLOB_RECURSE SOURCES "*.cpp")

    add_library(${PROJECT_NAME}_day_${DAY}_lib STATIC ${SOURCES}) 
endmacro()
