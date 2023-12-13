//
// Created by carlo on 2023/11/21.
//

#ifndef PRACTICA1_ESTRUCTURASLUCES_H
#define PRACTICA1_ESTRUCTURASLUCES_H

#include <glm/glm.hpp>

struct LuzAmbiental {
    glm::vec3 Ia;
};

struct LuzPuntual {
    glm::vec3 posicion;
    glm::vec3 Id;
    glm::vec3 Is;
    bool habilitada;
};

struct LuzDireccional {
    glm::vec3 direccion;
    glm::vec3 Id;
    glm::vec3 Is;
    bool habilitada;
};

struct LuzSpot {
    glm::vec3 posicion;
    glm::vec3 direccion;
    glm::vec3 Id;
    glm::vec3 Is;
    float aperturaCono;
    bool habilitada;
};

#endif //PRACTICA1_ESTRUCTURASLUCES_H
