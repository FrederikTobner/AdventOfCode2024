file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(${PROJECT_NAME}_day_1 ${SOURCES})

configure_file(input.txt input.txt COPYONLY)