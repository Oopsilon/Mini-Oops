cmake_minimum_required (VERSION 2.4)
project (lemon)

add_executable (lemon lemon.cxx)
target_link_libraries(lemon oopsRt)
