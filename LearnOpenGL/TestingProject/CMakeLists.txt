# CMakeList.txt : CMake project for TestingProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Add source to this project's executable.
add_executable (TestingProject "main.cpp" )

include_directories(${CMAKE_SOURCE_DIR}/Global_Include)

link_directories(${CMAKE_SOURCE_DIR}/Global_Libraries)
link_directories(${CMAKE_SOURCE_DIR}/Global_Sources)

#target_include_directories(TestingProject PUBLIC ${CMAKE_SOURCE_DIR}/Global_Includes)

add_library(
	glad
	${CMAKE_SOURCE_DIR}/Global_Include/glad/glad.h
	${CMAKE_SOURCE_DIR}/Global_Sources/glad.c
)

target_link_libraries(TestingProject ${CMAKE_SOURCE_DIR}/Global_Libraries/glfw3.lib)
target_link_libraries(TestingProject glad)