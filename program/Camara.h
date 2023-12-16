//
// Created by carlo on 2023/10/22.
//

#ifndef PRACTICA1_CAMARA_H
#define PRACTICA1_CAMARA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

namespace PAG {

    class Camara {

    private:
        // Atributos camara
        glm::vec3 posicionCamara;
        glm::vec3 vectorLookAt;
        glm::vec3 vectorArriba;
        glm::mat4 matrizVision;
        glm::vec3 vectorFrontal;

    private:
        // Atributos proyeccion
        glm::mat4 matrizProyeccion;
        float gradosEnRadianes;
        float ratioDeAspecto;
        float zNear;
        float zFar;

        // euler Angles
        float yaw;
        float pitch;


    private:
        // Atributos varios
        glm::vec2 ultimaPosicionRaton;
        bool primerMovimientoRaton;
    public:
        void setPrimerMovimientoRaton(bool primerMovimientoRaton);

    private:
        float anguloHorizontal = 3.14f;
        float anguloVertical = 0.0f;
    public:
        const glm::vec2 &getUltimaPosicionRaton() const;

        void setUltimaPosicionRaton(const glm::vec2 &ultimaPosicionRaton);
        void procesarMovimiento(double xpos, double ypos);

    public:
        // Atributos camara seteo y getters
        const glm::vec3 &getPosicionCamara() const;
        void setPosicionCamara(const glm::vec3 &posicionCamara);
        const glm::vec3 &getVectorLookAt() const;
        void setVectorLookAt(const glm::vec3 &vectorLookAt);
        const glm::vec3 &getVectorArriba() const;
        void setVectorArriba(const glm::vec3 &vectorArriba);
        glm::mat4 &getMatrizVision();
        glm::mat4 &getMatrizProyeccion();
        void setMatrizVision(const glm::mat4 &matrizVision);
        void setMatrizProyeccion(const glm::mat4 &matrizProyeccion);
        void actualizarVectorFrontal();

        // Métodos
        Camara(const glm::vec3 &posicionCamara, const glm::vec3 &vectorLookAt, const glm::vec3 &vectorArriba,
               float gradosEnRadianes, float ratioDeAspecto, float zNear, float zFar);
        Camara();
        void setCamara();

        // Métodos movimiento de cámara
        void movimientoArriba(float velocidadCamara);
        void movimientoAbajo(float velocidadCamara);
        void movimientoDerecha(float velocidadCamara);
        void movimientoIzquierda(float velocidadCamara);
        void panoramica(float a);
        void cabeceo(float a);

    };
}

#endif //PRACTICA1_CAMARA_H
