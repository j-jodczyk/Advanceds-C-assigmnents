cmake_minimum_required(VERSION 3.12)

add_executable(algos stdalgo.cpp)
target_link_libraries(algos PRIVATE NoForLoopAlgos)  

add_executable(iters stditer.cpp)  

