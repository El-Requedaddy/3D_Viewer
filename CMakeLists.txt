cmake_minimum_required(VERSION 3.26)
project(3D_Viewer)

set(CMAKE_CXX_STANDARD 17)

add_executable(3D_Viewer program/main.cpp
        program/Renderer.cpp
        program/Renderer.h
        program/singleton_template.h
        program/ShaderHandler.cpp
        program/ShaderHandler.h
        program/FileLoader.h
        program/FileLoader.cpp
        program/Camara.cpp
        program/Camara.h
        program/Modelos.cpp
        program/Modelos.h
        program/MallaModelo.cpp
        program/MallaModelo.h
        program/Estructuras.h
        program/GestorModelos.cpp
        program/GestorModelos.h
        program/Luz.cpp
        program/Luz.h
        program/EstructurasLuces.h
        program/lodepng.cpp
        program/lodepng.h
)

find_package(glfw3)
target_link_libraries(3D_Viewer glfw)

find_package(glew)
target_link_libraries(3D_Viewer GLEW::GLEW)

find_package(glm)
target_link_libraries(3D_Viewer glm::glm)

find_package(opengl_system)
target_link_libraries(3D_Viewer opengl::opengl)

find_package(assimp)
target_link_libraries(3D_Viewer assimp::assimp)