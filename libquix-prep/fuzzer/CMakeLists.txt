cmake_minimum_required(VERSION 3.15)
project(libquix-prep-fuzzer CXX)

set(SOURCE "fuzzer.cc")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_executable(libquix-prep-fuzzer ${SOURCE})
target_include_directories(libquix-prep-fuzzer PUBLIC ../include ${CMAKE_SOURCE_DIR}/libquix-core/include)
target_link_libraries(libquix-prep-fuzzer PUBLIC quix-prep)
add_dependencies(libquix-prep-fuzzer quix-prep)
