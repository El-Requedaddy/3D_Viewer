//
// Created by carlo on 2023/10/08.
//

#ifndef PRACTICA1_SHADERHANDLER_H
#define PRACTICA1_SHADERHANDLER_H

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Estructuras.h"
#include <vector>
#include "Modelos.h"

namespace PAG {

    class ShaderHandler {

    public:
        ShaderHandler();
        ~ShaderHandler();

    private:
        std::vector<GLuint> indicesSubrutinasFragment;
        GLuint idVS = 0; // Identificador del vertex shader
        GLuint idFS = 0; // Identificador del fragment shader
        GLuint idSP = 0; // Identificador del shader program

    public:
        GLuint getIdVs() const;
        void setIdVs(GLuint idVs);
        GLuint getIdFs() const;
        void setIdFs(GLuint idFs);
        GLuint getIdSp() const;
        void setIdSp(GLuint idSp);

    private:
        void comprobarCompilacion(GLint codigoShader);
        void incrementarID(GLuint &id);

    public:
        void creaShaderProgram(std::string nombreVertexShader, std::string nombreFragmentShader);
        unsigned int getUniform(std::string nombreUniform);
        void setearSubrutina(std::string uniformSubrutina, std::string subrutinaId, GLenum shadertype);
        void activarSubrutinas();
        void vaciarIndicesSubrutinas();
        void interrogarSubrutinas(); // Más debug que otra cosa, sujeto a ser eliminado en un producto real
    };

}

#endif //PRACTICA1_SHADERHANDLER_H
