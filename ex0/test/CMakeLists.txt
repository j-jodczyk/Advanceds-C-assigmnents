cmake_minimum_required(VERSION 3.12)

add_executable(test_print test_print.cpp)
target_link_libraries(test_print helper_functions)
add_test(NAME test_print COMMAND test_print)
set_tests_properties(test_print PROPERTIES
  PASS_REGULAR_EXPRESSION "1.1332" "9.99" "3.1"
)

add_executable(test_copy test_copy.cpp)
target_link_libraries(test_copy helper_functions)
add_test(NAME test_copy COMMAND test_copy)

add_executable(test_reset test_reset.cpp)
target_link_libraries(test_reset helper_functions)
add_test(NAME test_reset COMMAND test_reset)

add_executable(test_fill_uniform_random test_fill_uniform_random.cpp)
target_link_libraries(test_fill_uniform_random helper_functions)
add_test(NAME test_fill_uniform_random COMMAND test_fill_uniform_random)

add_executable(test_swap test_swap.cpp)
target_link_libraries(test_swap helper_functions)
add_test(NAME test_swap COMMAND test_swap)

add_executable(test_concat test_concat.cpp)
target_link_libraries(test_concat helper_functions)
add_test(NAME test_concat COMMAND test_concat)

add_executable(test_sort test_sort.cpp)
target_link_libraries(test_sort helper_functions)
add_test(NAME test_sort COMMAND test_sort)
