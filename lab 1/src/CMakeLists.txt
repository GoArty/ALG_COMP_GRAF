cmake_minimum_required(VERSION 3.0)
project(MyProject)

# Найдем библиотеки GLFW и OpenGL
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# Добавим исполняемый файл
add_executable(main main.cpp)

# Связываем исполняемый файл с библиотеками GLFW и OpenGL
target_link_libraries(main PRIVATE glfw OpenGL::GL)
