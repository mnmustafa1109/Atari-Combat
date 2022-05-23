cmake_minimum_required(VERSION 3.22)

# set the project name
project(Combat)

find_package(SFML 
  COMPONENTS 
    system window graphics network audio REQUIRED)


#Bring the headers, such as Student.h into the project
set(MY_HEADER_FILES
    include/home.hxx
)

set(MY_SOURCE_FILES
    src/main.cxx 
    src/home.cxx
)


add_executable(Combat
	${MY_HEADER_FILES}
	${MY_SOURCE_FILES}
)

# Link executable to required SFML libraries
target_link_libraries(Combat sfml-graphics)