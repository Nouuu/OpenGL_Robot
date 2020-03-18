cmake_minimum_required(VERSION 3.15)
project(soil_test)

set(CMAKE_CXX_STANDARD 14)

add_executable(soil_test main.cpp
        Camera.cpp
        Block.cpp
        Map.cpp
        include/SOIL.c
        include/image_DXT.c
        include/image_helper.c
        include/stb_image_aug.c
        include/Skybox.h)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ./include ./img ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(soil_test ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )