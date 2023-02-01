cmake_minimum_required(VERSION 3.12)

add_executable(Test_moveAssign Test_moveAssign.cpp testasserts.hpp)
target_link_libraries(Test_moveAssign PRIVATE List)
add_test(NAME Test_moveAssign COMMAND Test_moveAssign)

add_executable(Test_moveConstruct Test_moveConstruct.cpp testasserts.hpp)
target_link_libraries(Test_moveConstruct PRIVATE List)
add_test(NAME Test_moveConstruct COMMAND Test_moveConstruct)

add_executable(Test_copyAssign Test_copyAssign.cpp testasserts.hpp)
target_link_libraries(Test_copyAssign PRIVATE List)
add_test(NAME Test_copyAssign COMMAND Test_copyAssign)

add_executable(Test_copyConstruct Test_copyConstruct.cpp testasserts.hpp)
target_link_libraries(Test_copyConstruct PRIVATE List)
add_test(NAME Test_copyConstruct COMMAND Test_copyConstruct)