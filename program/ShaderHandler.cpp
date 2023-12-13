//
// Created by carlo on 2023/10/08.
//

#include "ShaderHandler.h"
#include "FileLoader.h"

PAG::ShaderHandler::ShaderHandler() {
}

void PAG::ShaderHandler::creaShaderProgram(std::string nombreVertexShader, std::string nombreFragmentShader) {

    try {
        idVS = glCreateShader (GL_VERTEX_SHADER);
        std::string castString = PAG::FileLoader::GetInstancia()->cargarArchivoATexto(nombreVertexShader);
        const GLchar* fuenteVS = castString.c_str();
        glShaderSource(idVS, 1, &fuenteVS, nullptr);
        glCompileShader(idVS);
        comprobarCompilacion(idVS);
    } catch (const std::runtime_error& e) {
        std::cout << "Error al compilar el vertex shader: " << e.what() << std::endl;
    }

    try {
        idFS = glCreateShader (GL_FRAGMENT_SHADER);
        std::string castString = PAG::FileLoader::GetInstancia()->cargarArchivoATexto(nombreFragmentShader);
        const GLchar* fuenteVS = castString.c_str();
        glShaderSource(idFS, 1, &fuenteVS, nullptr);
        glCompileShader(idFS);
        comprobarCompilacion(idFS);
    } catch (const std::runtime_error& e) {
        std::cout << "Error al compilar el fragment shader: " << e.what() << std::endl;
    }

    try {
        idSP = glCreateProgram ();
        glAttachShader(idSP, idVS);
        glAttachShader(idSP, idFS);
        glLinkProgram(idSP);
        // TODO: comprobar posibles errores de enlazado
        GLint resultadoEnlazado = 0;
        glGetProgramiv ( idSP, GL_LINK_STATUS, &resultadoEnlazado );
        if ( resultadoEnlazado == GL_FALSE )
        {
            // Ha habido un error y hay que recuperar su descripción, para saber qué ha pasado
            GLint tamMsj = 0;
            std::string mensaje = "";
            glGetProgramiv ( idSP, GL_INFO_LOG_LENGTH, &tamMsj );
            if ( tamMsj > 0 )
            {
                GLchar* mensajeFormatoC = new GLchar[tamMsj];
                GLint datosEscritos = 0;
                glGetProgramInfoLog ( idSP, tamMsj, &datosEscritos, mensajeFormatoC );
                mensaje.assign ( mensajeFormatoC );
                delete[] mensajeFormatoC;
                mensajeFormatoC = nullptr;
                throw std::runtime_error ( mensaje );
            }
        }
    } catch(const std::runtime_error& e) {
        std::cout << "Error al enlazar el programa: " << e.what() << std::endl;
    }

    interrogarSubrutinas();

}

// Verificar si hubo un error de compilación del shader
void PAG::ShaderHandler::comprobarCompilacion(GLint codigoShader) {
    GLint wasCompiled;
    glGetShaderiv( codigoShader, GL_COMPILE_STATUS, &wasCompiled );
    GLint logLength;
    glGetShaderiv( codigoShader, GL_INFO_LOG_LENGTH, &logLength );
    if (logLength > 0)
    {
        GLchar* log = new GLchar[ (std::size_t)logLength + 1 ];
        GLsizei charsWritten = 0;
        glGetShaderInfoLog( codigoShader, logLength, &charsWritten, log );
        std::cout << std::string( log );
    }
}

unsigned int PAG::ShaderHandler::getUniform(std::string nombreUniform) {
    const GLchar* nombreUniformCast = nombreUniform.c_str();
    unsigned int variableAux = glGetUniformLocation(idSP, nombreUniformCast);
    return variableAux;
}

/*
 * @param: Cadena de texto que representa la subrutina
 * @post: se asigna e indica la subrutina a usar
*/
void PAG::ShaderHandler::setearSubrutina(std::string uniformSubrutina, std::string subrutinaId, GLenum shadertype) {
    GLint tam = 0;
    glGetProgramStageiv ( idSP, GL_FRAGMENT_SHADER, GL_ACTIVE_SUBROUTINE_UNIFORMS, &tam );

    try {
        // Obtener la ubicación del uniforme de la subrutina
        GLint posUniform = glGetSubroutineUniformLocation(idSP, shadertype, uniformSubrutina.c_str());
        if (posUniform == -1) {
            throw std::runtime_error("No se ha podido localizar el uniform de la subrutina");
        }

        // Obtener el índice de la subrutina según su nombre
        GLuint indiceSubrutina = glGetSubroutineIndex(idSP, shadertype, subrutinaId.c_str());
        if (indiceSubrutina == GL_INVALID_INDEX) {
            throw std::runtime_error("No se ha podido localizar la implementación de la subrutina");
        }

        indicesSubrutinasFragment.push_back(indiceSubrutina);

    } catch (const std::exception& e) {
        std::cerr << "Excepción de la subrutina: " << e.what() << std::endl;
    }
}

void PAG::ShaderHandler::incrementarID(GLuint &id) {
    id++;
}

GLuint PAG::ShaderHandler::getIdVs() const {
    return idVS;
}

void PAG::ShaderHandler::setIdVs(GLuint idVs) {
    idVS = idVs;
}

GLuint PAG::ShaderHandler::getIdFs() const {
    return idFS;
}

void PAG::ShaderHandler::setIdFs(GLuint idFs) {
    idFS = idFs;
}

GLuint PAG::ShaderHandler::getIdSp() const {
    return idSP;
}

void PAG::ShaderHandler::setIdSp(GLuint idSp) {
    idSP = idSp;
}

PAG::ShaderHandler::~ShaderHandler() {

}

void PAG::ShaderHandler::interrogarSubrutinas() {
    std::cout << "Información sobre subrutinas"
              << "============================"
              << std::endl;
    GLint kk = 0;
    glGetProgramStageiv ( idSP, GL_FRAGMENT_SHADER
            , GL_ACTIVE_SUBROUTINE_UNIFORMS, &kk );
    std::cout << "Hay " << kk << " subrutinas que hay que configurar"
              << std::endl;
    for ( int i = 0; i < kk; i++ )
    { GLsizei tamNombre = 0;
        GLchar* texto = new GLchar [100];
        glGetActiveSubroutineUniformName ( idSP, GL_FRAGMENT_SHADER
                , i, 100, &tamNombre, texto );
        std::cout << "La subrutina " << i << " es " << std::string ( texto )
                  << std::endl;
        std::cout << "Las implementaciones disponibles para esta subrutina son:"
                  << std::endl;
        GLint kk2 = 0;
        glGetActiveSubroutineUniformiv ( idSP, GL_FRAGMENT_SHADER
                , i, GL_NUM_COMPATIBLE_SUBROUTINES, &kk2 );
        GLint* indices = new GLint [kk2];
        glGetActiveSubroutineUniformiv ( idSP, GL_FRAGMENT_SHADER
                , i, GL_COMPATIBLE_SUBROUTINES, indices );
        for ( int j = 0; j < kk2; j++ )
        { GLsizei tamNombre2 = 0;
            GLchar* texto2 = new GLchar[100];
            glGetActiveSubroutineName ( idSP, GL_FRAGMENT_SHADER
                    , indices[j], 100, &tamNombre2, texto2 );
            std::cout << "\tImplementación " << indices[j] << ": "
                      << std::string ( texto2 )
                      << std::endl;
        }
    }
}

/**
 * @brief Método que activa las subrutinas correspondientes mediante el vector de índices
 */
void PAG::ShaderHandler::activarSubrutinas() {
    glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, indicesSubrutinasFragment.size(), indicesSubrutinasFragment.data());
}

void PAG::ShaderHandler::vaciarIndicesSubrutinas() {
    indicesSubrutinasFragment.clear();
}
