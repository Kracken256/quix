cmake_minimum_required(VERSION 3.15)
project(libquix-prep CXX)

#================== CONFIGURE BUILD ==================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

#================== CALCULATE BUILD ID ==================
execute_process(COMMAND find ${CMAKE_CURRENT_SOURCE_DIR} -type f -name "*.*" -exec sha256sum {} \; COMMAND sha256sum
  OUTPUT_VARIABLE SHA256SUMS OUTPUT_STRIP_TRAILING_WHITESPACE)
string(REGEX REPLACE " .*" "" SHA256SUMS ${SHA256SUMS})
string(TOUPPER ${SHA256SUMS} SHA256SUMS)
string(SUBSTRING ${SHA256SUMS} 0 32 SHA256SUMS)
set(__TARGET_VERSION "\"QPREP_${SHA256SUMS}\"")
message(STATUS "libquix-prep VersionId: ${__TARGET_VERSION}")

#===================== BUILD LUA ======================
add_custom_target(
  quixlua
  COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/deps/lua CFLAGS='-fPIC'
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/deps/lua
)
set(LIB_QUIXLUA ${CMAKE_CURRENT_SOURCE_DIR}/deps/lua/liblua.a)
message(STATUS "libquix-prep: Building with Lua: ${LIB_QUIXLUA}")

#================== SET BUILD FLAGS ==================
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-return-type-c-linkage -D__TARGET_VERSION=\\\"undefined\\\"")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-return-type-c-linkage -D__TARGET_VERSION=\\\"${__TARGET_VERSION}\\\"")
else()
  message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}")
endif()

file(GLOB_RECURSE CXX_SOURCES "src/*.cc")

add_library(quix-prep STATIC ${CXX_SOURCES})
target_include_directories(quix-prep PUBLIC src "include"
  ${CMAKE_CURRENT_SOURCE_DIR}/../libquix-core/include
  ${CMAKE_CURRENT_SOURCE_DIR}/../libquix-lexer/include
  ${CMAKE_CURRENT_SOURCE_DIR}/../libquix-prep/deps)
target_link_libraries(quix-prep PUBLIC quix-core quix-lexer ${LIB_QUIXLUA} crypto)
add_dependencies(quix-prep quix-core quix-lexer quixlua)

add_library(quix-prep-shared SHARED ${CXX_SOURCES})
target_include_directories(quix-prep-shared PUBLIC src "include"
  ${CMAKE_CURRENT_SOURCE_DIR}/../libquix-core/include
  ${CMAKE_CURRENT_SOURCE_DIR}/../libquix-lexer/include
  ${CMAKE_CURRENT_SOURCE_DIR}/../libquix-prep/deps)
target_link_libraries(quix-prep-shared PUBLIC quix-core-shared quix-lexer-shared ${LIB_QUIXLUA} crypto)
add_dependencies(quix-prep-shared quix-core-shared quix-lexer-shared quixlua)
set_target_properties(quix-prep-shared PROPERTIES OUTPUT_NAME quix-prep)

if(BUILD_TESTING)
  add_subdirectory(tests)
  add_subdirectory(fuzzer)
endif()

install(TARGETS quix-prep-shared DESTINATION lib)
install(TARGETS quix-prep DESTINATION lib)
install(DIRECTORY include/ DESTINATION "include")
