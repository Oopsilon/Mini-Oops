cmake_minimum_required (VERSION 2.4)
project (LGen)

add_executable (LGen lemon.cxx)
target_link_libraries(LGen oops)
