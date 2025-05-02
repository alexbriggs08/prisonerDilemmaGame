cmake_minimum_required(VERSION 3.30)
project(prisonersDilemaGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(prisonersDilemaGame src/main.cpp
        src/config.h)

target_include_directories(prisonersDilemaGame PRIVATE dependencies)

find_library(OpenGL_LIBRARY OpenGL)
find_library(GLUT_LIBRARY GLUT)

target_link_libraries(prisonersDilemaGame
        ${OpenGL_LIBRARY}
        ${GLUT_LIBRARY}
)
