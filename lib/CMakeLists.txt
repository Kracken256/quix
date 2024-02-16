cmake_minimum_required(VERSION 3.15)
project(libj CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find C++20 source files
file(GLOB_RECURSE LIBJ_CXX_SOURCES "src/*.cc")

add_library(libj-static STATIC ${LIBJ_CXX_SOURCES})
target_include_directories(libj-static PUBLIC include)
target_compile_options(libj-static PRIVATE -O3 -Wall -Wextra -Werror -Wpedantic -flto -fvisibility=hidden -fvisibility-inlines-hidden -fno-rtti)
target_link_options(libj-static PRIVATE -flto)
target_link_libraries(libj-static PRIVATE -lstdc++ -lm -lpthread -lstdc++fs)
set_target_properties(libj-static PROPERTIES OUTPUT_NAME libj)

add_library(libj-shared SHARED ${LIBJ_CXX_SOURCES})
target_include_directories(libj-shared PUBLIC include)
target_compile_options(libj-shared PRIVATE -O3 -Wall -Wextra -Werror -Wpedantic -flto -fvisibility=hidden -fvisibility-inlines-hidden -fno-rtti)
target_link_options(libj-shared PRIVATE -flto)
target_link_libraries(libj-shared PRIVATE -lstdc++ -lm -lpthread -lstdc++fs)
set_target_properties(libj-shared PROPERTIES OUTPUT_NAME libj)
