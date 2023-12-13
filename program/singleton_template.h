//
// Created by carlo on 2023/09/25.
//

#ifndef PRACTICA1_SINGLETON_TEMPLATE_H
#define PRACTICA1_SINGLETON_TEMPLATE_H

#include <memory>
#include <GL/gl.h>
#include "FileLoader.h"

// No recuerdo como implementarlo, pero al menos está

template <class T>
class Singleton {

    public:

        static std::shared_ptr<T>& getInstance() {
            if (!instancia) {
                instancia = std::make_shared<T>();
            }
            return instancia;
        }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

protected:
    Singleton() {}

private:
    static std::shared_ptr<T> instancia;
};

template <typename T>
std::shared_ptr<T> Singleton<T>::instancia = nullptr;

#endif //PRACTICA1_SINGLETON_TEMPLATE_H
