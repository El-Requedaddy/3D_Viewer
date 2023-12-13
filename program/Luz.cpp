//
// Created by carlo on 2023/11/20.
//

#include <stdexcept>
#include "Luz.h"

// Constructor para luz ambiental
PAG::Luz::Luz(PAG::TipoLuz tipoLuz, glm::vec3 colorAmbiental)
        : tipoLuz(tipoLuz), Ia(colorAmbiental), habilitada(true) {

    if (tipoLuz != TipoLuz::AMBIENTE) {
        throw std::runtime_error("Tipo de luz no correspondiente al constructor invocado. Este constructor define una luz Ambiental");
    }

}

// Constructor para luz puntual
PAG::Luz::Luz(PAG::TipoLuz tipoLuz, glm::vec3 colorDifuso, glm::vec3 colorEspecular, glm::vec3 posicion)
        : tipoLuz(tipoLuz), Id(colorDifuso), Is(colorEspecular), posicion(posicion), direccion(glm::vec3(0.0f)), anguloAperturaSpot(0.0f), habilitada(true) {

    if (tipoLuz != TipoLuz::PUNTUAL) {
        throw std::runtime_error("Tipo de luz no correspondiente al constructor invocado. Este constructor define una luz Puntual");
    }

}

// Constructor para luz direccional
PAG::Luz::Luz(PAG::TipoLuz tipoLuz, glm::vec3 colorDifuso, glm::vec3 colorEspecular, glm::vec3 posicion, glm::vec3 direccion)
        : tipoLuz(tipoLuz), Id(colorDifuso), Is(colorEspecular), posicion(posicion), direccion(direccion), anguloAperturaSpot(0.0f), habilitada(true) {

    if (tipoLuz != TipoLuz::DIRECCIONAL) {
        throw std::runtime_error("Tipo de luz no correspondiente al constructor invocado. Este constructor define una luz Direccional");
    }

}

// Constructor para luz de punto con o sin spot
PAG::Luz::Luz(PAG::TipoLuz tipoLuz, glm::vec3 colorDifuso, glm::vec3 colorEspecular, glm::vec3 posicion,
              glm::vec3 direccion, float anguloSpot)
        : tipoLuz(tipoLuz), Id(colorDifuso), Is(colorEspecular), posicion(posicion),
          direccion(direccion), anguloAperturaSpot(anguloSpot), habilitada(true) {

    if (tipoLuz != TipoLuz::SPOT) {
        throw std::runtime_error("Tipo de luz no correspondiente al constructor invocado. Este constructor define una luz Spot");
    }

}

PAG::TipoLuz PAG::Luz::getTipoLuz() const {
    return tipoLuz;
}

const glm::vec3 &PAG::Luz::getPosicion() const {
    return posicion;
}

void PAG::Luz::setPosicion(const glm::vec3 &posicion) {
    Luz::posicion = posicion;
}

const glm::vec3 &PAG::Luz::getDireccion() const {
    return direccion;
}

void PAG::Luz::setDireccion(const glm::vec3 &direccion) {
    Luz::direccion = direccion;
}

const glm::vec3 &PAG::Luz::getIa() const {
    return Ia;
}

void PAG::Luz::setIa(const glm::vec3 &ia) {
    Ia = ia;
}

const glm::vec3 &PAG::Luz::getId() const {
    return Id;
}

void PAG::Luz::setId(const glm::vec3 &id) {
    Id = id;
}

const glm::vec3 &PAG::Luz::getIs() const {
    return Is;
}

void PAG::Luz::setIs(const glm::vec3 &is) {
    Is = is;
}

bool PAG::Luz::isHabilitada() const {
    return habilitada;
}

void PAG::Luz::setHabilitada(bool habilitada) {
    Luz::habilitada = habilitada;
}
