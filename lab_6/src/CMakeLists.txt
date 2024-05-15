cmake_minimum_required(VERSION 3.17)
project(MyProject)

# Найдем библиотеки GLFW и OpenGL
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLU REQUIRED)
include_directories(include)  

# Добавим исполняемый файл
add_executable(main main.cpp stb_image.h)

# Связываем исполняемый файл с библиотеками GLFW и OpenGL

target_link_libraries(main PRIVATE glfw OpenGL::GL ${GLUT_LIBRARY} ${GLU_LIBRARY})
     



