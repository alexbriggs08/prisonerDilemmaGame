cmake_minimum_required(VERSION 3.30)
project(prisonersDilemaGame)

set(CMAKE_CXX_STANDARD 20)

# OpenGL setup
if(APPLE)
    find_library(OPENGL_LIBRARY OpenGL REQUIRED)
    find_library(GLUT_LIBRARY GLUT REQUIRED)
endif()

add_executable(prisonersDilemaGame src/main.cpp)

if(APPLE)
    target_link_libraries(prisonersDilemaGame
            ${OPENGL_LIBRARY}
            ${GLUT_LIBRARY}
    )
endif()
