//
// Created by carlo on 2023/10/30.
//

#ifndef PRACTICA1_MODELOS_H
#define PRACTICA1_MODELOS_H

#include <vector>
#include "MallaModelo.h"
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <glm/glm.hpp>
#include "lodepng.h"

namespace PAG {

    class Modelos {
    public:
        Modelos(const char *path, glm::mat4 matrizModelado, float brillo, glm::vec3 colorAmbiental,
                glm::vec3 componenteDifuso, glm::vec3 exponenteEspecular);

    private:
        std::vector<MallaModelo*> malla;
        std::string directorio;
        glm::mat4 matrizModeladoModelo;
        bool activoEnEscena;
        GLuint idSP;
        GLuint idTextura;

    private:
        std::vector<Textura> texturasCargadas;

    private:
        // Atributos de material
        glm::vec3 colorAmbiente;
        glm::vec3 componenteDifuso;
        glm::vec3 exponenteEspecular;
        float especular;

    private:

        void cargarModelo(std::string path);
        void procesarNodo(aiNode *node, const aiScene *scene);
        MallaModelo *procesarMalla(aiMesh *mesh, const aiScene *scene);
        void cargarTextura(std::string rutaTextura);

    public:
        virtual ~Modelos();

    public:
        glm::vec3 getColorAmbiente() const;
        void setColorAmbiente(glm::vec3 colorAmbiente);
        glm::vec3 getComponenteDifuso() const;
        void setComponenteDifuso(glm::vec3 componenteDifuso);
        glm::vec3 getExponenteEspecular() const;
        void setExponenteEspecular(glm::vec3 exponenteEspecular);
        float getEspecular() const;
        void setEspecular(float especular);
        GLuint getIdTextura() const;
        void setIdTextura(GLuint idTextura);

    public:
        std::vector<Vertice> obtenerVerticesModelo();
        std::vector<unsigned int> obtenerIndicesModelo();
        MallaModelo &getMallaModelo(int indice);
        const int getNumeroMallas();
        const glm::mat4 &getMatrizModeladoModelo() const;
        void setMatrizModeladoModelo(const glm::mat4 &matrizModeladoModelo);
        bool isActivoEnEscena() const;
        void setActivoEnEscena(bool activoEnEscena);
        GLuint getIdSp() const;
        void setIdSp(GLuint idSp);
    };

}

#endif //PRACTICA1_MODELOS_H
