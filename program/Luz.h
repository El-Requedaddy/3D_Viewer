//
// Created by carlo on 2023/11/20.
//

#ifndef PRACTICA1_LUZ_H
#define PRACTICA1_LUZ_H

#include <glm/glm.hpp>

namespace PAG {

    enum class TipoLuz {
        AMBIENTE,
        PUNTUAL,
        DIRECCIONAL,
        SPOT
    };

    class Luz {

    private:
        TipoLuz tipoLuz;
        bool habilitada;

    private:
        glm::vec3 posicion;

    public:
        TipoLuz getTipoLuz() const;
        const glm::vec3 &getPosicion() const;
        void setPosicion(const glm::vec3 &posicion);
        const glm::vec3 &getDireccion() const;
        void setDireccion(const glm::vec3 &direccion);
        const glm::vec3 &getIa() const;
        void setIa(const glm::vec3 &ia);
        const glm::vec3 &getId() const;
        void setId(const glm::vec3 &id);
        const glm::vec3 &getIs() const;
        void setIs(const glm::vec3 &is);
        bool isHabilitada() const;
        void setHabilitada(bool habilitada);

    private:
        // Posición para "direccional/spot"
        glm::vec3 direccion; // Dirección para luz "direccional/spot"
        glm::vec3 Ia; // Color "luz ambiental"
        glm::vec3 Id, Is; // Colores difusa, especular de "puntual/direccional"
        float anguloAperturaSpot; // Ángulo apertura spot

    public:
        Luz(TipoLuz tipoLuz, glm::vec3 colorAmbiental); // Constructor luz ambiente
        Luz(TipoLuz tipoLuz, glm::vec3 colorDifuso, glm::vec3 colorEspecular, glm::vec3 posicion); // Constructor luz puntual
        Luz(TipoLuz tipoLuz, glm::vec3 colorDifuso, glm::vec3 colorEspecular, glm::vec3 posicion, glm::vec3 direccion); // Constructor luz direccional
        Luz(TipoLuz tipoLuz, glm::vec3 colorDifuso, glm::vec3 colorEspecular, glm::vec3 posicion, glm::vec3 direccion, float anguloSpot);
    };

}

#endif //PRACTICA1_LUZ_H
