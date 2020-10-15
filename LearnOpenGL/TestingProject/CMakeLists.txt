# CMakeList.txt : CMake project for TestingProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Add source to this project's executable.

include_directories(${CMAKE_SOURCE_DIR}/Global_Include)
link_directories(${CMAKE_SOURCE_DIR}/Global_Libraries)
file (GLOB global_sources 
	"${CMAKE_SOURCE_DIR}/Global_Sources/*.c"
	"${CMAKE_SOURCE_DIR}/Global_Sources/*.cpp")

#file (COPY "${CMAKE_SOURCE_DIR}/Resources" DESTINATION TestingProject)

add_executable (TestingProject "main.cpp" ${global_sources})

message(${CMAKE_SOURCE_DIR}/Resources/)
add_custom_command(TARGET TestingProject POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/Resources/ $<TARGET_FILE_DIR:TestingProject>/Resources)

target_link_libraries(TestingProject ${CMAKE_SOURCE_DIR}/Global_Libraries/glfw3.lib)