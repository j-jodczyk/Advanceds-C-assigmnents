cmake_minimum_required(VERSION 3.12)

add_executable(TestA_ClassMembers TestA_ClassMembers.cpp testasserts.hpp)
target_link_libraries(TestA_ClassMembers PRIVATE Distribution)
add_test(NAME TestA_ClassMembers COMMAND TestA_ClassMembers)

add_executable(TestB_Vector TestB_Vector.cpp testasserts.hpp)
target_link_libraries(TestB_Vector PRIVATE Distribution)
add_test(NAME TestB_Vector COMMAND TestB_Vector)

add_executable(TestC_SpaceVector TestC_SpaceVector.cpp testasserts.hpp)
target_link_libraries(TestC_SpaceVector PRIVATE Distribution SpaceVector)
add_test(NAME TestC_SpaceVector COMMAND TestC_SpaceVector)

add_executable(TestD_List TestD_List.cpp testasserts.hpp)
target_link_libraries(TestD_List PRIVATE Distribution SpaceVector)
add_test(NAME TestD_List COMMAND TestD_List)

add_executable(TestE_Deque TestE_Deque.cpp testasserts.hpp)
target_link_libraries(TestE_Deque PRIVATE Distribution SpaceVector)
add_test(NAME TestE_Deque COMMAND TestE_Deque)
