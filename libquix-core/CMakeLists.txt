cmake_minimum_required(VERSION 3.15)
project(libquix-core CXX)

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
set(__TARGET_VERSION "\"QCORE_${SHA256SUMS}\"")
message(STATUS "libquix-core VersionId: ${__TARGET_VERSION}")

#================== SET BUILD FLAGS ==================
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti -D__TARGET_VERSION=\\\"undefined\\\"")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti -D__TARGET_VERSION=\\\"${__TARGET_VERSION}\\\"")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--version-script,${CMAKE_CURRENT_SOURCE_DIR}/symexport.map")
else()
  message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}")
endif()

file(GLOB_RECURSE CXX_SOURCES "src/*.cc")

add_library(quix-core STATIC ${CXX_SOURCES})
target_include_directories(quix-core PUBLIC src "include")

add_library(quix-core-shared SHARED ${CXX_SOURCES})
target_include_directories(quix-core-shared PUBLIC src "include")
set_target_properties(quix-core-shared PROPERTIES OUTPUT_NAME quix-core)

install(TARGETS quix-core-shared DESTINATION lib)
install(TARGETS quix-core DESTINATION lib)
install(DIRECTORY include/ DESTINATION "include")
