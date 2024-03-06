cmake_minimum_required(VERSION 3.15)
project(quixcc CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find C++20 source files
file(GLOB_RECURSE QUIXCC_CXX_SOURCES "src/*.cc")

add_executable(quixcc ${QUIXCC_CXX_SOURCES})
target_include_directories(quixcc PRIVATE "src" ${CMAKE_CURRENT_SOURCE_DIR}/../libquixcc/include)
target_compile_options(quixcc PRIVATE -g -Wall -Wextra -Wpedantic -Werror -O3 -flto)
target_link_options(quixcc PRIVATE -flto)
target_link_directories(quixcc PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../libquixcc)
target_link_libraries(quixcc PRIVATE libquixcc)
add_dependencies(quixcc libquixcc)

