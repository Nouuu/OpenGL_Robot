cmake_minimum_required(VERSION 3.15)
project(OPENGL_ROBOT)

set(CMAKE_CXX_STANDARD 14)

add_executable(OPENGL_ROBOT main.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(OPENGL_ROBOT ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )