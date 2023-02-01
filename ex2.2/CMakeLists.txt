cmake_minimum_required(VERSION 3.19)
include(CMakePrintHelpers)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "" FORCE)
set(CMAKE_CXX_STANDARD "17" CACHE STRING "" FORCE)
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE BOOL "" FORCE)
set(CMAKE_CXX_EXTENSIONS OFF CACHE BOOL "" FORCE)

project(Ex2.2 LANGUAGES CXX)

# compiler specific for clang and gnu
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # strict compilation
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -pedantic")
  # settings for "-D CMAKE_BUILD_TYPE=ASAN"
  set(CMAKE_CXX_FLAGS_ASAN "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -fsanitize=address -fno-omit-frame-pointer -fno-common -g" CACHE STRING "" FORCE)
  set(CMAKE_EXE_LINKER_FLAGS_ASAN "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} -fsanitize=address -g" CACHE STRING "" FORCE)
  set(CMAKE_SHARED_LINKER_FLAGS_ASAN "${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO} -fsanitize=address -g" CACHE STRING "" FORCE)
endif()

# Distribution header only library
add_library(Distribution INTERFACE)
#target_sources(Distribution INTERFACE include/Distribution.hpp)
target_include_directories(Distribution INTERFACE include)

# SpaceVector header only library
add_library(SpaceVector INTERFACE)
#target_sources(SpaceVector INTERFACE include/SpaceVector.hpp)
target_include_directories(SpaceVector INTERFACE include)

# add tests from subfolder
enable_testing()
add_subdirectory("test")

# benchmark executable
option(BUILD_BENCHMARK "Build the executables" OFF)

if(BUILD_BENCHMARK)
  add_executable(benchmark src/benchmark.cpp)
  target_link_libraries(benchmark PRIVATE Distribution SpaceVector)
endif(BUILD_BENCHMARK)
