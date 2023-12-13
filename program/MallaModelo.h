//
// Created by carlo on 2023/10/30.
//

#ifndef PRACTICA1_MALLAMODELO_H
#define PRACTICA1_MALLAMODELO_H

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Estructuras.h"

namespace PAG {

    class MallaModelo {

    private:
        GLuint VAO, VBO, EBO;
        std::vector<Vertice> vertices;
        std::vector<unsigned int> indices;
        std::vector<Textura> texturas;

    public:
        GLuint *getVao();
        GLuint *getVbo();
        GLuint *getEbo();
        GLuint getVaoNor();
        void setVao(GLuint vao);
        void setVbo(GLuint vbo);
        void setEbo(GLuint ebo);

    private:
        void InicializacionMalla();

    public:
        // mesh data
        const std::vector<Vertice> &getVertices() const;
        void setVertices(const std::vector<Vertice> &vertices);
        const std::vector<unsigned int> &getIndices() const;
        void setIndices(const std::vector<unsigned int> &indices);
        const std::vector<Textura> &getTexturas() const;
        void setTexturas(const std::vector<Textura> &texturas);
        //std::vector<Textura> textures;
        MallaModelo &obtenerMalla();
        MallaModelo(std::vector<Vertice> vertices, std::vector<unsigned int> indices, std::vector<Textura> texturas);
        virtual ~MallaModelo();
    };
}

#endif //PRACTICA1_MALLAMODELO_H
