//
// Created by carlo on 2023/10/09.
//

#ifndef PRACTICA1_FILELOADER_H
#define PRACTICA1_FILELOADER_H

#include <iostream>
#include <memory>
#include <string>
#include <fstream>

namespace PAG {
    class FileLoader {

    protected:
        static std::shared_ptr<PAG::FileLoader> fileLoader;


    public:
        FileLoader();
        FileLoader(const FileLoader &obj) = delete;
        static std::shared_ptr<FileLoader> GetInstancia();
        std::string cargarArchivoATexto(std::string nombreArchivo);
    };

}

#endif //PRACTICA1_FILELOADER_H
