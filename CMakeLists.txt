cmake_minimum_required(VERSION 3.15)
project(CLANK)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

add_executable(CLANK
        src/main.cpp
        src/Camera.cpp
        src/Block.cpp
        src/Map.cpp
        src/Box.cpp
        src/Bolt.cpp
        include/SOIL.c
        include/image_DXT.c
        include/image_helper.c
        include/stb_image_aug.c
        src/Arms.cpp
        src/Clank.cpp
        src/Body.cpp
        src/Head.cpp
        src/Legs.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(./src ./include ./img ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(CLANK ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})