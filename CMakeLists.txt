cmake_minimum_required(VERSION 3.15)
project(j-language)

add_subdirectory(lib)
add_subdirectory(jcc)

if (BUILD_TESTING)
    add_subdirectory(test)
endif()