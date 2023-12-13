//
// Created by carlo on 2023/10/09.
//

#include "FileLoader.h"

std::shared_ptr<PAG::FileLoader> PAG::FileLoader::fileLoader = nullptr;

PAG::FileLoader::FileLoader() {}

std::string PAG::FileLoader::cargarArchivoATexto(std::string nombreArchivo) {
    std::ifstream fich(nombreArchivo);
    if (!fich.is_open()) {
        std::cout << "Error al abrir el archivo";
    }

    std::string texto;
    std::string textoFinal;
    while (std::getline(fich, texto)) {
        textoFinal += texto + '\n';
    }
    //std::cout << textoFinal << std::endl;
    return textoFinal;
}

std::shared_ptr<PAG::FileLoader> PAG::FileLoader::GetInstancia() {
    if (!fileLoader) {
        fileLoader = std::make_shared<FileLoader>();
        return fileLoader;
    } else {
        return fileLoader;
    }
}
