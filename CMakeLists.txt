cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)

# set the project name
project(Combat)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
add_library(irrKlang SHARED IMPORTED)
set_property(TARGET irrKlang PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/irrKlang/libIrrKlang.so")

#Bring the headers, such as Student.h into the project
set(MY_HEADER_FILES
include/input.hxx
include/shader.hxx
include/shape.hxx
include/texture.hxx
include/stb_image.h
    include/movement.hxx
    include/resourceman.hxx
    include/vehicle.hxx
    include/bullet.hxx
    include/obstacle.hxx
    include/uuid.hxx
    include/map.hxx
    include/game.hxx
    include/main.hxx
    include/player.hxx
)

set(MY_SOURCE_FILES
    src/glad.c
    src/input.cxx
    src/shader.cxx
    src/shape.cxx
    src/texture.cxx
    src/stb_image.c
    src/movement.cxx
    src/resourceman.cxx
    src/vehicle.cxx
    src/bullet.cxx
    src/map.cxx
    src/uuid.cxx
    src/obstacle.cxx
    src/game.cxx
    src/main.cxx 
    src/player.cxx
)


add_executable(Combat
${MY_HEADER_FILES}
${MY_SOURCE_FILES}
)

target_link_libraries(Combat glfw OpenGL::GL )
target_link_libraries(Combat irrKlang)




# Link executable to required SFML libraries
