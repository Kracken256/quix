cmake_minimum_required(VERSION 3.15)
project(jcc CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find C++20 source files
file(GLOB_RECURSE JCC_CXX_SOURCES "src/*.cc")


# Get LLVM flags from llvm-config --cxxflags
execute_process(COMMAND llvm-config --cxxflags
                OUTPUT_VARIABLE LLVM_CXX_FLAGS
                OUTPUT_STRIP_TRAILING_WHITESPACE)

# Get LLVM flags from llvm-config --ldflags
execute_process(COMMAND llvm-config --ldflags
                OUTPUT_VARIABLE LLVM_LD_FLAGS
                OUTPUT_STRIP_TRAILING_WHITESPACE)

# Get LLVM flags from llvm-config --system-libs --libs
execute_process(COMMAND llvm-config --system-libs --libs
                OUTPUT_VARIABLE LLVM_LIBS
                OUTPUT_STRIP_TRAILING_WHITESPACE)

add_executable(jcc ${JCC_CXX_SOURCES})
target_include_directories(jcc PRIVATE "src" ${CMAKE_CURRENT_SOURCE_DIR}/../lib/public)
target_compile_options(jcc PRIVATE -g -Wall -Wextra -Wpedantic -Werror -O3 -flto  ${LLVM_CXX_FLAGS})
target_link_options(jcc PRIVATE -flto ${LLVM_LD_FLAGS})
target_link_directories(jcc PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../lib)
target_link_libraries(jcc PRIVATE libj.so ${LLVM_LIBS} crypto)
add_dependencies(jcc j-shared)

