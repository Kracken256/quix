cmake_minimum_required(VERSION 3.15)
project(libjcc-tests CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
    FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add the libjcc library unit tests
file(GLOB_RECURSE TEST_SOURCES "unit/*.cc")

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

enable_testing()

add_executable(libjcc-tests ${TEST_SOURCES})
target_include_directories(libjcc-tests PRIVATE  ${CMAKE_CURRENT_SOURCE_DIR}/../include "${CMAKE_CURRENT_SOURCE_DIR}/../internal")
target_link_directories(libjcc-tests PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../../libjcc)
target_link_options(libjcc-tests PRIVATE ${LLVM_LD_FLAGS})
target_compile_options(libjcc-tests PRIVATE -Wall -Wextra -Werror)
target_link_libraries(libjcc-tests j GTest::gtest_main ${LLVM_LIBS})
add_dependencies(libjcc-tests j-shared)
add_test(NAME libjcc-tests COMMAND libjcc-tests)

include(GoogleTest)
gtest_discover_tests(libjcc-tests)
