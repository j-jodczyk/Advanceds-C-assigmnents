cmake_minimum_required(VERSION 3.12)

add_executable(TestA_dereference TestA_dereference.cpp testasserts.hpp)
target_link_libraries(TestA_dereference PRIVATE List)
add_test(NAME TestA_dereference COMMAND TestA_dereference)

add_executable(TestB_increment TestB_increment.cpp testasserts.hpp)
target_link_libraries(TestB_increment PRIVATE List)
add_test(NAME TestB_increment COMMAND TestB_increment)

add_executable(TestC_decrement TestC_decrement.cpp testasserts.hpp)
target_link_libraries(TestC_decrement PRIVATE List)
add_test(NAME TestC_decrement COMMAND TestC_decrement)

add_executable(TestD_decrement_end TestD_decrement_end.cpp testasserts.hpp)
target_link_libraries(TestD_decrement_end PRIVATE List)
add_test(NAME TestD_decrement_end COMMAND TestD_decrement_end)

add_executable(TestE_member_access TestE_member_access.cpp testasserts.hpp)
target_link_libraries(TestE_member_access PRIVATE List)
add_test(NAME TestE_member_access COMMAND TestE_member_access)

add_executable(TestF_comparisons TestF_comparisons.cpp testasserts.hpp)
target_link_libraries(TestF_comparisons PRIVATE List)
add_test(NAME TestF_comparisons COMMAND TestF_comparisons)

add_executable(TestG_loops TestG_loops.cpp testasserts.hpp)
target_link_libraries(TestG_loops PRIVATE List)
add_test(NAME TestG_loops COMMAND TestG_loops)

add_executable(TestH_const_access TestH_const_access.cpp testasserts.hpp)
target_link_libraries(TestH_const_access PRIVATE List)
add_test(NAME TestH_const_access COMMAND TestH_const_access)

add_executable( TestI_stdlib_compatibility  TestI_stdlib_compatibility.cpp testasserts.hpp)
target_link_libraries( TestI_stdlib_compatibility PRIVATE List)
add_test(NAME  TestI_stdlib_compatibility COMMAND  TestI_stdlib_compatibility)


