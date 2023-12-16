//
// Created by carlo on 2023/11/05.
//

#ifndef PRACTICA1_GESTORMODELOS_H
#define PRACTICA1_GESTORMODELOS_H

#include "Modelos.h"

namespace PAG {

    class GestorModelos {

    private:
        std::vector<Modelos*> modelosEscena;
        GLuint idTexturaModelos;

    public:
        void creaModelo(const char *path, glm::mat4 matrizModelado, std::string rutaTextura, std::string rutaNormal, float brillo, glm::vec3 colorAmbiental,
                        glm::vec3 componenteDifuso, glm::vec3 exponenteEspecular);
        void cargarTextura(std::string rutaTextura);
        ~GestorModelos();
        GestorModelos();
        // Añadir o eliminar de la escena modelos
        void eliminarModeloEscena();
        void añadirModelosEscena();
        void activarTexturasModelo(GLuint idSP, int indice);
        void desactivarTexturasModelo(GLuint idSP, int indice);

        std::vector<Modelos*>& getModelosEscena() {
            return modelosEscena;
        }
    };

}

#endif //PRACTICA1_GESTORMODELOS_H
