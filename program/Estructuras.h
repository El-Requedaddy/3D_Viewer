//
// Created by carlo on 2023/11/01.
//
#ifndef PRACTICA1_ESTRUCTURAS_H
#define PRACTICA1_ESTRUCTURAS_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <string>

// Estructura global vertices
struct Vertice {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Textura {
    GLint id;
    std::string tipo;
    std::string path;
};



#endif //PRACTICA1_ESTRUCTURAS_H
