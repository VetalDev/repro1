cmake_minimum_required(VERSION 2.8)

project(simp_repro)
#set(STB_INCLUDE_PATH, "./thirdparty/stb")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")
add_executable(${PROJECT_NAME} "simple_reproducer.cpp")
 #target_include_directories(qt-vulkan PUBLIC INCLUDE_DIRECTORIES "./thirdparty/stb" )
 #target_include_directories(qt-vulkan PUBLIC INCLUDE_DIRECTORIES "./thirdparty/tinyobjloader" )
 #target_include_directories(qt-vulkan PUBLIC INCLUDE_DIRECTORIES STB_INCLUDE_PATH )
 #message("current dir = ${STB_INCLUDE_PATH}")
 #message($(STB_INCLUDE_PATH))
#add_executable(${PROJECT_NAME} "22-descriptor-sets.cpp")
#target_link_libraries(${PROJECT_NAME} glfw vulkan dl X11 )
target_link_libraries(${PROJECT_NAME} glfw dl X11 GL GLEW)