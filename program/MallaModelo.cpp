//
// Created by carlo on 2023/10/30.
//

#include "MallaModelo.h"

PAG::MallaModelo::MallaModelo(std::vector<Vertice> vertices, std::vector<unsigned int> indices, std::vector<Textura> texturas) {
    this->vertices = vertices;
    this->indices = indices;
    this->texturas = texturas;
}

const std::vector<Vertice> &PAG::MallaModelo::getVertices() const {
    return vertices;
}

void PAG::MallaModelo::setVertices(const std::vector<Vertice> &vertices) {
    MallaModelo::vertices = vertices;
}

const std::vector<unsigned int> &PAG::MallaModelo::getIndices() const {
    return indices;
}

void PAG::MallaModelo::setIndices(const std::vector<unsigned int> &indices) {
    MallaModelo::indices = indices;
}

GLuint *PAG::MallaModelo::getVao() {
    return &VAO;
}

GLuint PAG::MallaModelo::getVaoNor() {
    return VAO;
}

GLuint *PAG::MallaModelo::getVbo() {
    return &VBO;
}

GLuint *PAG::MallaModelo::getEbo() {
    return &EBO;
}

void PAG::MallaModelo::setVao(GLuint vao) {
    VAO = vao;
}

void PAG::MallaModelo::setVbo(GLuint vbo) {
    VBO = vbo;
}

void PAG::MallaModelo::setEbo(GLuint ebo) {
    EBO = ebo;
}

PAG::MallaModelo &PAG::MallaModelo::obtenerMalla() {
    return *this;
}

const std::vector<Textura> &PAG::MallaModelo::getTexturas() const {
    return texturas;
}

void PAG::MallaModelo::setTexturas(const std::vector<Textura> &texturas) {
    MallaModelo::texturas = texturas;
}

PAG::MallaModelo::~MallaModelo() {

}
