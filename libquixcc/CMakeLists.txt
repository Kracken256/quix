cmake_minimum_required(VERSION 3.15)
project(libquixcc CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find C++20 source files
file(GLOB_RECURSE LIBQUIX_CXX_SOURCES "src/*.cc")

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

add_library(libquixcc SHARED ${LIBQUIX_CXX_SOURCES})
target_include_directories(libquixcc PUBLIC "internal" include)
if (CMAKE_BUILD_TYPE STREQUAL "Release") 
    target_compile_options(libquixcc PRIVATE -Wall -Wextra -Wpedantic -Werror -Wno-error=unused-parameter ${LLVM_CXX_FLAGS} -frandom-seed=${RANDOM_NUMBER} -Wno-error=unused-variable -fPIC -O3 -flto -s -fvisibility=hidden -fvisibility-inlines-hidden )
    target_link_options(libquixcc PRIVATE ${LLVM_LD_FLAGS} -O3 -flto -Wl,--version-script,${CMAKE_CURRENT_SOURCE_DIR}/only_quixcc_exports.map)
    add_custom_command(TARGET libquixcc POST_BUILD COMMAND strip -s $<TARGET_FILE:libquixcc>)
else()
    target_compile_options(libquixcc PRIVATE -g -Wall -Wextra -Werror -Wno-error=unused-parameter -Wpedantic ${LLVM_CXX_FLAGS} -frandom-seed=${RANDOM_NUMBER} -Wno-error=unused-variable -fPIC)
    target_link_options(libquixcc PRIVATE ${LLVM_LD_FLAGS})
endif()
target_link_libraries(libquixcc PRIVATE -lstdc++ -lm -lpthread -lstdc++fs crypto ${LLVM_LIBS})
set_target_properties(libquixcc PROPERTIES OUTPUT_NAME quixcc)

if (BUILD_TESTING)
    add_subdirectory(test)
endif()