cmake_minimum_required(VERSION 3.15)
project(libj CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find C++20 source files
file(GLOB_RECURSE LIBJ_CXX_SOURCES "src/*.cc")

# Get LLVM flags from llvm-config --cxxflags
execute_process(COMMAND llvm-config --cxxflags
                OUTPUT_VARIABLE LLVM_CXX_FLAGS
                OUTPUT_STRIP_TRAILING_WHITESPACE)

# Get LLVM flags from llvm-config --ldflags 
execute_process(COMMAND llvm-config --ldflags
OUTPUT_VARIABLE LLVM_LD_FLAGS
OUTPUT_STRIP_TRAILING_WHITESPACE)

# Get LLVM flags from llvm-config  --libs
execute_process(COMMAND llvm-config --libs --system-libs
OUTPUT_VARIABLE LLVM_LIBS
OUTPUT_STRIP_TRAILING_WHITESPACE)

# Get random number
execute_process(COMMAND echo -n 0x | openssl rand -hex 4
OUTPUT_VARIABLE RANDOM_NUMBER
OUTPUT_STRIP_TRAILING_WHITESPACE)

add_library(j-shared SHARED ${LIBJ_CXX_SOURCES})
target_include_directories(j-shared PUBLIC include public)
target_compile_options(j-shared PRIVATE -g -O3 -Wall -Wextra -Wpedantic ${LLVM_CXX_FLAGS} -frandom-seed=${RANDOM_NUMBER} -Wno-error=unused-variable)
target_link_options(j-shared PRIVATE ${LLVM_LD_FLAGS})
target_link_libraries(j-shared PRIVATE -lstdc++ -lm -lpthread -lstdc++fs -lcrypto ${LLVM_LIBS})
set_target_properties(j-shared PROPERTIES OUTPUT_NAME j)
