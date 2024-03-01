cmake_minimum_required(VERSION 3.15)
project(jcc CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find C++20 source files
file(GLOB_RECURSE JCC_CXX_SOURCES "src/*.cc")

add_executable(jcc ${JCC_CXX_SOURCES})
target_include_directories(jcc PRIVATE "src" ${CMAKE_CURRENT_SOURCE_DIR}/../lib/public)
target_compile_options(jcc PRIVATE -g -Wall -Wextra -Wpedantic -Werror -O3 -flto)
target_link_options(jcc PRIVATE -flto)
target_link_directories(jcc PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../lib)
target_link_libraries(jcc PRIVATE j crypto)
add_dependencies(jcc j-shared)

