file(GLOB_RECURSE SOURCES "*.cpp")
add_library(${PROJECT_NAME}_shared_lib STATIC ${SOURCES})
if(MSVC)
    target_compile_options(${PROJECT_NAME}_shared_lib PRIVATE /std:c++latest)
endif()