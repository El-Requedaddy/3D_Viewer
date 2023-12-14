//
// Created by carlo on 2023/09/15.
//

#ifndef PRACTICA1_RENDERER_H
#define PRACTICA1_RENDERER_H

#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include "ShaderHandler.h"
#include "FileLoader.h"
#include "Camara.h"
#include <vector>
#include "GestorModelos.h"
#include "EstructurasLuces.h"
#include "Luz.h"

namespace PAG {

    enum TipoRenderizado{
        alambre,
        relleno
    };

    enum TipoCalculoColor{
        material,
        textura
    };

    class Renderer {

            private:
            // Instancias de elementos tales como la cámara, shaderHandler y demás
            Camara* camara;
            GestorModelos* gestorModelos;
            TipoRenderizado renderizado = relleno;
            TipoCalculoColor modoCalculoColor = textura;

            ShaderHandler* shaderAmbiental;
            ShaderHandler* shaderPuntual;
            ShaderHandler* shaderDireccional;
            std::vector<Luz*> lucesEscena;

            private:
            // Variables gestión específicas
            float anchuraPantalla;
            GLuint idVAO = 0;
            GLuint idVBO = 0; // Identificador del vertex buffer object
            GLuint idIBO = 0; // Identificador del index buffer object

            public:
            float getAnchuraPantalla() const;
            void setAnchuraPantalla(float anchuraPantalla);
            float getAlturaPantalla() const;
            void setAlturaPantalla(float alturaPantalla);

            void setTipoCalculoColorMaterial();
            void setTipoCalculoColorTextura();
            void setTipoRenderizadoAlambre();
            void setTipoRenderizadoRelleno();

            private:
            float alturaPantalla;

            protected:
            static std::shared_ptr<PAG::Renderer> renderer;

            public:
            Renderer();
            Renderer(const Renderer& obj) = delete;
            GLuint getIdVao() const;
            void setIdVao(GLuint idVao);
            GLuint getIdVbo() const;
            void setIdVbo(GLuint idVbo);
            GLuint getIdIbo() const;
            void setIdIbo(GLuint idIbo);

            virtual ~Renderer();
            static std::shared_ptr<Renderer> GetInstancia();

            void Refrescar();
            void RefrescarColor(GLfloat  r, GLfloat  g, GLfloat b, GLfloat  alpha);
            void SetViewport(int x, int y, int anchura, int altura);
            void SetWindowShouldClose(GLFWwindow *window);
            void TestProfundidad();
            void inicializaOpenGL();
            void seteoCamara();
            void movimientoRatonCamara(double xpos, double ypos, bool clickIzquierdoMantenido);
            void movimientoTeclasCamara(int glcode);
            void crearModelo(const char *path, glm::mat4 matrizModelado, std::string rutaTextura);
            void refrescarModelos();
            void dibujadoModelos();
            void anadirEliminarModelos(bool eliminar);
            void dibujoModeloMalla(MallaModelo &malla);
            void InicializacionArraysModeloMalla(std::vector<Vertice> vertices, std::vector<unsigned int> indices, std::vector<Textura> texturas, MallaModelo &malla);
            void renderizarEscena(Modelos* modelo);
            void asignarModeloArrays();
            ShaderHandler* obtenerShaderParaLuz(int indice);
            void anadirLuces(Luz* luz);
            void inicializarShaders();
            void activarTextura(GLuint idTextura, GLuint idSP);
            void desactivarTextura(GLuint idTextura, GLuint idSP);
            void actualizarSubrutinasShaders();

            // Añadir luces
            void crearLuzPuntual(glm::vec3 colorDifuso, glm::vec3 colorEspecular, glm::vec3 posicion);
            void crearluzDireccional(glm::vec3 colorDifuso, glm::vec3 colorEspecular, glm::vec3 direccion);
    };

}

#endif //PRACTICA1_RENDERER_H
