cmake_minimum_required(VERSION 3.12)
include(CMakePrintHelpers)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "" FORCE)
set(CMAKE_CXX_STANDARD "17" CACHE STRING "" FORCE)
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE BOOL "" FORCE)
set(CMAKE_CXX_EXTENSIONS OFF CACHE BOOL "" FORCE)

project(Ex3.3 LANGUAGES CXX)

# compiler specific for clang and gnu
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # strict compilation
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -pedantic")
  # settings for "-D CMAKE_BUILD_TYPE=ASAN"
  set(CMAKE_CXX_FLAGS_ASAN "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -fsanitize=address -fno-omit-frame-pointer -fno-common -g" CACHE STRING "" FORCE)
  set(CMAKE_EXE_LINKER_FLAGS_ASAN "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} -fsanitize=address -g" CACHE STRING "" FORCE)
  set(CMAKE_SHARED_LINKER_FLAGS_ASAN "${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO} -fsanitize=address -g" CACHE STRING "" FORCE)  
endif()

enable_testing()

option(USE_CURL "try finding libcurl" ON)
FIND_PACKAGE( CURL ) 
if((NOT CURL_FOUND) OR (NOT USE_CURL)) # use provided mock-up
  add_subdirectory("curlmock")
  add_library(dummy INTERFACE)
  add_library(CURL::libcurl ALIAS dummy)    
else() # use provided libcurl-wrapper
  add_subdirectory("curl")
endif()

# tcache header-only library
add_library(tcache INTERFACE)
target_include_directories(tcache INTERFACE include)
target_link_libraries(tcache INTERFACE cppcurl)

add_subdirectory("test")
add_subdirectory("app")


