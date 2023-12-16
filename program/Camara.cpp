//
// Created by carlo on 2023/10/22.
//

#include "Camara.h"

PAG::Camara::Camara(const glm::vec3 &posicionCamara, const glm::vec3 &vectorLookAt, const glm::vec3 &vectorArriba,
                    float gradosEnRadianes, float ratioDeAspecto, float zNear, float zFar) : posicionCamara(
                    posicionCamara), vectorLookAt(vectorLookAt), vectorArriba(vectorArriba), gradosEnRadianes(gradosEnRadianes),
                    ratioDeAspecto(ratioDeAspecto), zNear(zNear), zFar(zFar) {

    // Sacamos las matrices correspondientes a la camara
    ratioDeAspecto = 1024 / 576;
    matrizVision = glm::lookAt(posicionCamara, vectorLookAt, vectorArriba);
    matrizProyeccion = glm::perspective(glm::radians(gradosEnRadianes), ratioDeAspecto, zNear, zFar);
    // La ultima posicion del raton al instante de inicializar la clase es 0
    ultimaPosicionRaton.x = 0;
    ultimaPosicionRaton.y = 0;
    yaw = -90.0f;
    pitch = 0.0f;
    primerMovimientoRaton = true;
}

// Constructor
PAG::Camara::Camara() {
    matrizProyeccion = glm::perspective(glm::radians(gradosEnRadianes), ratioDeAspecto, 0.1f, 100.0f);
}

void PAG::Camara::procesarMovimiento(double xpos, double ypos) {
    //Cambio la ultima posicion del raton
    if (primerMovimientoRaton) {
        ultimaPosicionRaton.x = xpos;
        ultimaPosicionRaton.y = ypos;
        primerMovimientoRaton = false;
    }
    double diferenciaX = xpos - ultimaPosicionRaton.x;
    double diferenciaY = ultimaPosicionRaton.y - ypos;
    ultimaPosicionRaton.x = xpos;
    ultimaPosicionRaton.y = ypos;
    float sensitividad = 0.3f;
    diferenciaX *= sensitividad;
    diferenciaY *= sensitividad;

    yaw += diferenciaX;
    pitch += diferenciaY;

    if(pitch > 89.0f)
        pitch =  89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direccionCamara;
    direccionCamara.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direccionCamara.y = sin(glm::radians(pitch));
    direccionCamara.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    vectorLookAt = glm::normalize(direccionCamara);
}

void PAG::Camara::movimientoArriba(float velocidadCamara) {
    glm::vec3 delante = velocidadCamara * vectorLookAt;
    posicionCamara += delante;
    std::cout << "La posicion de la camara es: " << posicionCamara.x << "," << posicionCamara.y << ", " << posicionCamara.z;
}

void PAG::Camara::movimientoAbajo(float velocidadCamara) {
    posicionCamara -= velocidadCamara * vectorLookAt;
}

void PAG::Camara::movimientoIzquierda(float velocidadCamara) {
    posicionCamara += glm::normalize(glm::cross(vectorArriba, vectorLookAt)) * velocidadCamara;
}

void PAG::Camara::movimientoDerecha(float velocidadCamara) {
    posicionCamara -= glm::normalize(glm::cross(vectorArriba, vectorLookAt)) * velocidadCamara;
}

const glm::vec3 &PAG::Camara::getPosicionCamara() const {
    return posicionCamara;
}

void PAG::Camara::setPosicionCamara(const glm::vec3 &posicionCamara) {
    Camara::posicionCamara = posicionCamara;
}

const glm::vec3 &PAG::Camara::getVectorLookAt() const {
    return vectorLookAt;
}

void PAG::Camara::setVectorLookAt(const glm::vec3 &vectorLookAt) {
    Camara::vectorLookAt = vectorLookAt;
}

const glm::vec3 &PAG::Camara::getVectorArriba() const {
    return vectorArriba;
}

void PAG::Camara::setVectorArriba(const glm::vec3 &vectorArriba) {
    Camara::vectorArriba = vectorArriba;
}

glm::mat4 &PAG::Camara::getMatrizVision() {
    matrizVision = glm::lookAt(posicionCamara, posicionCamara + vectorLookAt, vectorArriba);
    return matrizVision;
}

glm::mat4 &PAG::Camara::getMatrizProyeccion() {
    matrizProyeccion = glm::perspective(glm::radians(gradosEnRadianes), ratioDeAspecto, zNear, zFar);
    return matrizProyeccion;
}

void PAG::Camara::setMatrizVision(const glm::mat4 &matrizVision) {
    Camara::matrizVision = matrizVision;
}

void PAG::Camara::setMatrizProyeccion(const glm::mat4 &matrizProyeccion) {
    Camara::matrizProyeccion = matrizProyeccion;
}

const glm::vec2 &PAG::Camara::getUltimaPosicionRaton() const {
    return ultimaPosicionRaton;
}

void PAG::Camara::setUltimaPosicionRaton(const glm::vec2 &ultimaPosicionRaton) {
    Camara::ultimaPosicionRaton = ultimaPosicionRaton;
}

void PAG::Camara::panoramica(float a) {
    vectorLookAt.x += a;
}

void PAG::Camara::cabeceo(float a) {
    vectorLookAt.y += a;
}

void PAG::Camara::setPrimerMovimientoRaton(bool primerMovimientoRaton) {
    this->primerMovimientoRaton = primerMovimientoRaton;
}
