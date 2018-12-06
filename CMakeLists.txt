cmake_minimum_required(VERSION 3.12)

project(RG104-evader C)

set(CMAKE_C_STANDARD 11)

link_libraries(GL)
link_libraries(GLU)
link_libraries(glut)

add_executable(RG104-evader main.c)