cmake_minimum_required(VERSION 3.12)

add_executable(App main.cpp)
target_link_libraries(App PRIVATE cppcurl)
target_link_libraries(App PRIVATE tcache)
target_link_libraries(App PRIVATE CURL::libcurl)
