cmake_minimum_required(VERSION 3.17)
project(main)

# Найдем библиотеки GLFW и OpenGL
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARY})



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")
set(SRC_LIST stb_image.h main.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} glfw OpenGL ${GLEW_LIBRARIES})
