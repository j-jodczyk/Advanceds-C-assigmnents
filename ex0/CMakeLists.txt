cmake_minimum_required(VERSION 3.12)
set(CMAKE_EXPORT_COMPILE_COMMANDS true CACHE BOOL "")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(CMakePrintHelpers)

project(ex0 CXX)

add_compile_options(-std=c++17)
add_compile_options(-Werror -Wall -pedantic)
add_compile_options(-fsanitize=address)
add_compile_options(-Wno-unused-variable)
add_link_options(-fsanitize=address)

add_library(helper_functions SHARED src/helper_functions.cpp include/helper_functions.hpp)
target_include_directories(helper_functions PUBLIC include)

enable_testing()
add_subdirectory(test)