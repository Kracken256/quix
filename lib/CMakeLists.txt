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

# Get LLVM flags from llvm-config --system-libs --libs
execute_process(COMMAND llvm-config --system-libs --libs
OUTPUT_VARIABLE LLVM_LIBS
OUTPUT_STRIP_TRAILING_WHITESPACE)


add_library(j-static STATIC ${LIBJ_CXX_SOURCES})
target_include_directories(j-static PUBLIC include public)
target_compile_options(j-static PRIVATE -g -O3 -Wall -Wextra -Werror -Wpedantic -flto -fno-rtti -fPIC ${LLVM_CXX_FLAGS} -Wno-error=unused-variable)
target_link_options(j-static PRIVATE -flto ${LLVM_LD_FLAGS})
target_link_libraries(j-static PRIVATE -lstdc++ -lm -lpthread -lstdc++fs -lcrypto ${LLVM_LIBS})
set_target_properties(j-static PROPERTIES OUTPUT_NAME j)

add_library(j-shared SHARED ${LIBJ_CXX_SOURCES})
target_include_directories(j-shared PUBLIC include public)
target_compile_options(j-shared PRIVATE -g -O3 -Wall -Wextra -Werror -Wpedantic -flto -fno-rtti -fPIC ${LLVM_CXX_FLAGS} -Wno-error=unused-variable)
target_link_options(j-shared PRIVATE -flto ${LLVM_LD_FLAGS})
target_link_libraries(j-shared PRIVATE -lstdc++ -lm -lpthread -lstdc++fs -lcrypto ${LLVM_LIBS})
set_target_properties(j-shared PROPERTIES OUTPUT_NAME j)
