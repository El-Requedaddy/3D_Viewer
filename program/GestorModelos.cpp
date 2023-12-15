//
// Created by carlo on 2023/11/05.
//

#include "GestorModelos.h"

void PAG::GestorModelos::creaModelo(const char *path, glm::mat4 matrizModelado, std::string rutaTextura) {
    Modelos* modelo = new Modelos(path, matrizModelado);
    if (!rutaTextura.empty()) {
        if (idTexturaModelos == 1) { // TODO cambiar esto y que funcione bien de forma natural
            modelo->setIdTextura(2);
        } else {
            modelo->setIdTextura(this->idTexturaModelos);
        }
        cargarTextura(rutaTextura);
    }
    modelosEscena.push_back(modelo);
}

PAG::GestorModelos::GestorModelos() {
    this->idTexturaModelos = 1;
}

PAG::GestorModelos::~GestorModelos() {
    // Desvinculamos y limpiamos los VAO. También eliminamos modelos
    // Recorremos los modelos para obtener las texturas a liberar y las liberamos
    glBindVertexArray(0);
    GLuint id;
    for (int i = 0; i < modelosEscena.size(); i++) {
        for (int j = 0; j < modelosEscena[i]->getNumeroMallas(); j++) {
            id = modelosEscena[i]->getIdTextura();
            glDeleteTextures(1, &id);
            glDeleteBuffers(1, modelosEscena[i]->getMallaModelo(j).getVao());
            glDeleteVertexArrays(1, modelosEscena[i]->getMallaModelo(j).getVao());
        }
        delete modelosEscena[i];
        modelosEscena[i] = nullptr;
    }

}

/**
 * @brief Carga una textura desde un archivo PNG.
 * @param rutaTextura Ruta del archivo PNG que contiene la textura.
 * @throws std::runtime_error Si la carga de la textura falla se libera esta excepción.
 * @post La textura se carga en OpenGL con los píxeles de la imagen.
 * @note Esta función asume que la textura está almacenada en formato RGBA.
 *       La imagen se invierte verticalmente para que coincida con las coordenadas de textura de OpenGL.
 */
void PAG::GestorModelos::cargarTextura(std::string rutaTextura) {
/** Carga un png de disco https://lodev.org/lodepng */
    std::vector<unsigned char> imagen; // Los píxeles de la imagen
    unsigned ancho, alto;
    unsigned error = lodepng::decode (imagen, ancho, alto, rutaTextura);
    if (error) {
        std::string mensaje = rutaTextura + " no se pudo cargar de forma satisfactoria";
        throw std::runtime_error(mensaje);
    }

    // La textura se carga del revés, así que vamos a darle la vuelta
    unsigned char *imgPtr = &imagen[0];
    int numeroDeComponentesDeColor = 4;
    int incrementoAncho = ancho * numeroDeComponentesDeColor; // Ancho en bytes
    unsigned char* top = nullptr;
    unsigned char* bot = nullptr;
    unsigned char temp = 0;
    for (int i = 0; i < alto / 2; i++) {
        top = imgPtr + i * incrementoAncho;
        bot = imgPtr + (alto - i - 1) * incrementoAncho;

        for (int j = 0; j < incrementoAncho; j++) {
            temp = *top;
            *top = *bot;
            *bot = temp;
            ++top;
            ++bot;
        }
    }

    // Finalmente, pasamos la textura a OpenGL con sus correspondientes parámetros
    glGenTextures ( 1, &idTexturaModelos );
    glBindTexture ( GL_TEXTURE_2D, idTexturaModelos );
    // Cómo resolver la minificación. En este caso, le decimos que utilice mipmaps, y que aplique interpolación lineal
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    // Cómo resolver la magnificación. En este caso, le decimos que utilice mipmaps, y que aplique interpolación lineal
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    // Cómo pasar de coordenadas de textura a coordenadas en el espacio de la textura en horizontal
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    // Cómo pasar de coordenadas de textura a coordenadas en el espacio de la textura en vertical
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, ancho, alto, 0, GL_RGBA,GL_UNSIGNED_BYTE, imagen.data() );
    glGenerateTextureMipmap (idTexturaModelos);
    // Aumentamos el ID para las próximas texturas

    // Un error tiene lugar dado que la primera textura que se carga si aumenta unidad por si misma
    //TODO arreglar error y que el incremento sea constante
    if (idTexturaModelos > 1) {
        idTexturaModelos++;
    }
}

void PAG::GestorModelos::eliminarModeloEscena() {
    // Recorremos y desactivamos el modelo que encontremos
    // No se elimina explícitamente puesto que se supone que se reutiliza después
    for (int i = 0; i < modelosEscena.size(); i++) {
        if (modelosEscena[i]->isActivoEnEscena()) {
            modelosEscena[i]->setActivoEnEscena(false);
            return;
        }
    }
}

void PAG::GestorModelos::añadirModelosEscena() {
    // Igual que el de eliminar pero cambiando valores booleanos
    for (int i = 0; i < modelosEscena.size(); i++) {
        if (!modelosEscena[i]->isActivoEnEscena()) {
            modelosEscena[i]->setActivoEnEscena(true);
            return;
        }
    }
}