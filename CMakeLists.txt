cmake_minimum_required(VERSION 3.26)
project(3D_Viewer)

set(CMAKE_CXX_STANDARD 17)

# Define la versión de tu proyecto
set(3D_Viewer_VERSION_MAJOR 1)
set(3D_Viewer_VERSION_MINOR 0)

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

include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "3D_Viewer")
set(CPACK_PROJECT_VERSION_MAJOR ${3D_Viewer_VERSION_MAJOR})
set(CPACK_PROJECT_VERSION_MINOR ${3D_Viewer_VERSION_MINOR})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_GENERATOR "ZIP")
include(CPack)