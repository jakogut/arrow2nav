cmake_minimum_required(VERSION 3.0)

project(arrow2nav)

add_executable(arrow2nav arrow2nav.c)
target_compile_options(arrow2nav PRIVATE -Wall -Wextra)

install(TARGETS arrow2nav RUNTIME DESTINATION bin)
