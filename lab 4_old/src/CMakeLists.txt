cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0072 NEW)

project(MyProject)

# Найдем библиотеки GLFW и OpenGL
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLU REQUIRED)

# Добавим исполняемый файл
add_executable(main main.cpp)

# Связываем исполняемый файл с библиотеками GLFW и OpenGL
target_link_libraries(main PRIVATE glfw OpenGL::GL ${GLUT_LIBRARY} ${GLU_LIBRARY})
