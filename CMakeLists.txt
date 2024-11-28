cmake_minimum_required(VERSION 3.26)
project(project C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS    "-Werror=vla -Wall -pedantic -Wno-format -Wno-unused-parameter -fexceptions -fstack-protector-strong -std=c99 -Wextra -Werror=implicit-function-declaration")
set(CMAKE_CXX_FLAGS  "-Wall -pedantic -Wno-format -Wno-unused-parameter -fexceptions -fstack-protector-strong")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/map.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(project apsc142project.c colours.c map.c game.c ghost.c)
add_executable(tests tests.cpp colours.c map.c game.c ghost.c)

