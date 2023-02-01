cmake_minimum_required(VERSION 3.12)

add_executable(TestA_rref TestA_rref.cpp testasserts.hpp)
target_link_libraries(TestA_rref PRIVATE Widget)
add_test(NAME TestA_rref COMMAND TestA_rref)

add_executable(TestB_lref TestB_lref.cpp testasserts.hpp)
target_link_libraries(TestB_lref PRIVATE Widget)
add_test(NAME TestB_lref COMMAND TestB_lref)

add_executable(TestC_value TestC_value.cpp testasserts.hpp)
target_link_libraries(TestC_value PRIVATE Widget)
add_test(NAME TestC_value COMMAND TestC_value)
