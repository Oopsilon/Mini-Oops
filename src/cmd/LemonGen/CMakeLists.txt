cmake_minimum_required (VERSION 2.4)
project (LemonGen)

add_executable (LemonGen lemon.cxx)
target_link_libraries(LemonGen oops)
