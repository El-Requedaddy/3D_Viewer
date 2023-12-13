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
    std::cout << ratioDeAspecto;
    matrizVision = glm::lookAt(posicionCamara, vectorLookAt, vectorArriba);
    matrizProyeccion = glm::perspective(glm::radians(gradosEnRadianes), ratioDeAspecto, zNear, zFar);
    // La ultima posicion del raton al instante de inicializar la clase es 0
    ultimaPosicionRaton.x = 0;
    ultimaPosicionRaton.y = 0;
}

// Constructor
PAG::Camara::Camara() {
    matrizProyeccion = glm::perspective(glm::radians(gradosEnRadianes), ratioDeAspecto, 0.1f, 100.0f);
}

void PAG::Camara::procesarMovimiento(double diferenciaX, double diferenciaY, double x, double y) {
    //Cambio la ultima posicion del raton
    ultimaPosicionRaton.x = x;
    ultimaPosicionRaton.y = y;
    float velocidadRaton = 3.0f;

    // Angulos de camara calculados respecto a la resolución
    anguloHorizontal += velocidadRaton * 3 * float(1024/2 - diferenciaX );
    anguloVertical   += velocidadRaton * 3 * float( 768/2 - diferenciaY );

    // Calculo simple: http://www.numericana.com/answer/trig.gif
    glm::vec3 direccion(cos(anguloVertical) * sin(anguloHorizontal), sin(anguloVertical), cos(anguloVertical) * cos(anguloHorizontal));
    glm::vec3 vectorDerecha = glm::vec3(sin(anguloHorizontal - 3.14f/2.0f), 0, cos(anguloVertical - 3.14f/2.0f));
    glm::vec3 up = glm::cross( vectorDerecha, direccion );

    vectorLookAt = posicionCamara + direccion;
    vectorArriba = up;
    std::cout << "El vector LookAt resultante es: " << vectorLookAt.x << std::endl;
}

void PAG::Camara::movimientoArriba() {
    std::cout << "Hola" << std::endl;
    posicionCamara.y += 1;
}

void PAG::Camara::movimientoAbajo() {
    posicionCamara.y -= 1;
}

void PAG::Camara::movimientoIzquierda() {
    posicionCamara.x -= 1;
    posicionCamara.z -= 1;
}

void PAG::Camara::movimientoDerecha() {
    posicionCamara.x += 1;
    posicionCamara.z += 1;
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
    matrizVision = glm::lookAt(posicionCamara, vectorLookAt, vectorArriba);
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
