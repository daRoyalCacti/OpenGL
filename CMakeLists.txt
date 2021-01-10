cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project("OpenGl")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)

add_executable(Generate main.cpp)
add_library(GLAD glad.c)
target_link_libraries(Generate GLAD)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(ASSIMP REQUIRED)


target_include_directories(Generate PUBLIC
	                           $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
				                              $<INSTALL_INTERFACE:include>)


target_link_libraries(Generate glfw)
target_link_libraries(Generate OpenGL::GL)
target_link_libraries(Generate assimp)
target_link_libraries(Generate ${CMAKE_DL_LIBS})

#include_directories("/home/george/Documents/Projects/Libraries/")
