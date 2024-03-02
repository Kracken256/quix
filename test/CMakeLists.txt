cmake_minimum_required(VERSION 3.15)
project(libj-tests CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# include(FetchContent)
#     FetchContent_Declare(
#     googletest
#     URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
# )
# # For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

# # Add the libj library unit tests
# file(GLOB_RECURSE TEST_SOURCES "unit/*.cc")

# add_executable(libj-tests ${TEST_SOURCES})
# target_include_directories(libj-tests PRIVATE  ${CMAKE_CURRENT_SOURCE_DIR}/../lib/include ${CMAKE_CURRENT_SOURCE_DIR}/../lib/public )
# target_link_directories(libj-tests PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../lib)
# target_compile_options(libj-tests PRIVATE -Wall -Wextra -Werror -O0)
# target_link_libraries(libj-tests GTest::gtest_main libj.so)
# add_dependencies(libj-tests j-shared)

# include(GoogleTest)
# gtest_discover_tests(libj-tests)
