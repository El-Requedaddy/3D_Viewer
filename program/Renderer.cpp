//
// Created by carlo on 2023/09/15.
//
#include "Renderer.h"

std::shared_ptr<PAG::Renderer> PAG::Renderer::renderer = nullptr;

PAG::Renderer::Renderer() {
    glEnable(GL_BLEND);
    gestorModelos = new GestorModelos();
    shaderAmbiental = nullptr;
    shaderPuntual = nullptr;
    shaderDireccional = nullptr;
}

std::shared_ptr<PAG::Renderer> PAG::Renderer::GetInstancia() {
    if (!renderer) {
        renderer = std::make_shared<Renderer>();
        return renderer;
    } else {
        return renderer;
    }
}

void PAG::Renderer::anadirLuces(Luz* luz) {
    lucesEscena.push_back(luz);
}

void PAG::Renderer::Refrescar() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
    dibujadoModelos();
}

void PAG::Renderer::RefrescarColor(GLfloat  r, GLfloat  g, GLfloat  b, GLfloat  alpha) {
    glClearColor ( r, g, b, alpha );
}

void PAG::Renderer::SetViewport(int x, int y, int anchura, int altura) {
    glViewport ( 0, 0, anchura, altura );
}

void PAG::Renderer::SetWindowShouldClose(GLFWwindow *window) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void PAG::Renderer::TestProfundidad() {
    glEnable ( GL_DEPTH_TEST );
    glDepthFunc (GL_LEQUAL);
}

/**
* Método para inicializar los parámetros globales de OpenGL
*/
void PAG::Renderer::inicializaOpenGL() {
    glClearColor (1, 1, 1, 1);
    TestProfundidad();
    glEnable ( GL_MULTISAMPLE );
    glEnable(GL_BLEND);
}

void PAG::Renderer::seteoCamara() {
    // Valores default al inicializar
    glm::vec3 posicionCamara = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 vectorLookAt = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 vectorUp = glm::vec3(0.0f, 1.0f, 0.0f);
    float gradosRadianes = 45.0f;
    float zNear = 0.1f;
    float zFar = 100.0f;

    // Inicializamos la camara con todos los atributos necesarios
    camara = new Camara(posicionCamara, vectorLookAt, vectorUp, gradosRadianes, 1.3, zNear, zFar);
}

void PAG::Renderer::movimientoRatonCamara(double xpos, double ypos, bool clickIzquierdoMantenido) {
    camara->procesarMovimiento(xpos, ypos);
}

void PAG::Renderer::movimientoTeclasCamara(int glcode, float velocidadCamara) {
    if (glcode == GLFW_KEY_UP) {
        camara->movimientoArriba(velocidadCamara);
    }
    if (glcode == GLFW_KEY_DOWN) {
        camara->movimientoAbajo(velocidadCamara);
    }
    if (glcode == GLFW_KEY_LEFT) {
        camara->movimientoIzquierda(velocidadCamara);
    }
    if (glcode == GLFW_KEY_RIGHT) {
        camara->movimientoDerecha(velocidadCamara);
    }

    if (glcode == GLFW_KEY_P) {
        camara->panoramica(0.05);
    }
    if (glcode == GLFW_KEY_C) {
        camara->cabeceo(0.05);
    }
    if (glcode == GLFW_KEY_O) {
        camara->panoramica(-0.05);
    }
    if (glcode == GLFW_KEY_X) {
        camara->cabeceo(-0.05);
    }

}

float PAG::Renderer::getAnchuraPantalla() const {
    return anchuraPantalla;
}

void PAG::Renderer::setAnchuraPantalla(float anchuraPantalla) {
    Renderer::anchuraPantalla = anchuraPantalla;
}

float PAG::Renderer::getAlturaPantalla() const {
    return alturaPantalla;
}

void PAG::Renderer::setAlturaPantalla(float alturaPantalla) {
    Renderer::alturaPantalla = alturaPantalla;
}

PAG::Renderer::~Renderer() {
    for (int i = 0; i < lucesEscena.size(); i++) {
        delete lucesEscena[i];
        lucesEscena[i] = nullptr;
    }
    lucesEscena.clear();

    delete camara;
    camara = nullptr;

    delete gestorModelos;
    gestorModelos = nullptr;

    delete shaderAmbiental;
    shaderAmbiental = nullptr;

    delete shaderPuntual;
    shaderPuntual = nullptr;

    delete shaderDireccional;
    shaderDireccional = nullptr;
}

/**
 * @brief Crea un modelo y lo agrega al gestor de modelos.
 *
 * @param path Ruta al archivo del modelo.
 * @param matrizModelado Matriz de transformación del modelo.
 * @param rutaTextura Ruta que indica la textura con la que se inicializa el modelo.
 *
 * @note Si no se manda textura se debe pasar un valor "".
 *
 * @post El modelo se crea y se agrega al gestor de modelos.
 * @post Se asignan los datos del modelo a los arrays necesarios.
 * @post La textura se asigna al modelo mediante el constructor.
 */
void PAG::Renderer::crearModelo(const char *path, glm::mat4 matrizModelado, std::string rutaTextura, std::string rutaNormal, float brillo, glm::vec3 colorAmbiental,
                                glm::vec3 componenteDifuso, glm::vec3 exponenteEspecular) {
    gestorModelos->creaModelo(path, matrizModelado, rutaTextura, rutaNormal, brillo, colorAmbiental, componenteDifuso, exponenteEspecular);
    asignarModeloArrays();
}

void PAG::Renderer::anadirEliminarModelos(bool eliminar) {
    if (eliminar) {
        gestorModelos->eliminarModeloEscena();
    } else {
        gestorModelos->añadirModelosEscena();
    }
}

/**
 * @brief Procesa lo relacionado con el dibujado de modelos de la escena, desde la iluminación a el dibujo de mallas
 * @post Los modelos son dibujados en escena junto a toda gestión del shader y sus subrutinas y uniformes
 * @note Este método no se encarga solo de dibujar modelos como tal, para ello tenemos el método de renderizado. Aquí
 *       se gestiona lo necesario
 */
void PAG::Renderer::dibujadoModelos() {
    std::vector<Modelos*> modelos = gestorModelos->getModelosEscena();
    if ( modelos.size () > 0 ) {
        for ( int j = 0; j < lucesEscena.size (); j++ ) { // Bucle de renderizado en sí, es decir, cada luz se renderiza junto al modelo

            TipoLuz tipoLuz;
            ShaderHandler *shader = obtenerShaderParaLuz(j); // Obtenemos un shader para procesar la luz

            // Activamos shader
            glUseProgram ( shader->getIdSp () );

            // Activamos subrutinas pertinentes
            shader->activarSubrutinas();

            if ( j == 0 ) { // Elegimos como aplicar el Alpha Blending en función de si es la primera luz o no
                glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
            }
            else {
                glBlendFunc ( GL_SRC_ALPHA, GL_ONE );
            }

            for ( int i = 0; i < modelos.size (); i++ ) {

                // Cálculo general de todos los shaders
                glm::mat4 matrizModelado = modelos[i]->getMatrizModeladoModelo ();
                glm::mat4 matrizModeladoVision = camara->getMatrizVision () * matrizModelado;
                glm::mat4 matrizModeladoComposicion = camara->getMatrizProyeccion () * camara->getMatrizVision () * matrizModelado;


                // Obtenemos uniformes de las luces y asignamos dichos uniforms en función de las luces introducidas en escena
                if (lucesEscena[j]->getTipoLuz() == TipoLuz::AMBIENTE) {
                    unsigned int luzAmbientalUniform = shader->getUniform ( "luzAmbiental" );
                    glUniform3fv ( luzAmbientalUniform, 1, glm::value_ptr ( lucesEscena[j]->getIa () ) );

                } else if ( lucesEscena[j]->getTipoLuz() == TipoLuz::PUNTUAL) {
                    unsigned int posicionUniform = shader->getUniform ( "posicion" );
                    unsigned int IdUniform = shader->getUniform ( "Id" );
                    unsigned int IsUniform = shader->getUniform ( "Is" );
                    unsigned int luzPosUniform = shader->getUniform ( "luzPos" ); // Vertex para el normal mapping

                    // Vinculamos las uniform de las luces
                    glm::vec3 posicion = glm::vec3((camara->getMatrizVision()) * glm::vec4(lucesEscena[j]->getPosicion(), 1.0));
                    glm::vec3 posicionId = lucesEscena[j]->getId ();
                    glm::vec3 posicionIS = lucesEscena[j]->getIs ();
                    glUniform3fv ( posicionUniform, 1, glm::value_ptr ( posicion ) );
                    glUniform3fv ( IdUniform, 1, glm::value_ptr ( lucesEscena[j]->getId () ) );
                    glUniform3fv ( IsUniform, 1, glm::value_ptr ( lucesEscena[j]->getIs () ) );

                    unsigned int matrizTraspuetaInversaUniform = shader->getUniform ( "matrizMVit" );
                    glm::mat4 matrizMVit = glm::transpose(glm::inverse(matrizModeladoVision)); // Traspuesta de la inversa de la matriz de modelado-vision
                    glUniformMatrix4fv ( matrizTraspuetaInversaUniform, 1, GL_FALSE, glm::value_ptr ( matrizMVit ) );

                } else if (lucesEscena[j]->getTipoLuz() == TipoLuz::DIRECCIONAL) {
                    unsigned int posicionUniform = shader->getUniform ( "direccion" );
                    unsigned int IdUniform = shader->getUniform ( "Id" );
                    unsigned int IsUniform = shader->getUniform ( "Is" );
                    unsigned int luzPosUniform = shader->getUniform ( "luzDir" ); // Vertex para el normal mapping
                    // Vinculamos las uniform de las luces
                    glm::vec3 posicion = glm::vec3((camara->getMatrizVision()) * glm::vec4(lucesEscena[j]->getDireccion(), 1.0));
                    glm::vec3 posicionId = lucesEscena[j]->getId ();
                    glm::vec3 posicionIS = lucesEscena[j]->getIs ();
                    glUniform3fv ( posicionUniform, 1, glm::value_ptr ( posicion ) );
                    glUniform3fv ( IdUniform, 1, glm::value_ptr ( lucesEscena[j]->getId () ) );
                    glUniform3fv ( IsUniform, 1, glm::value_ptr ( lucesEscena[j]->getIs () ) );

                    unsigned int matrizTraspuetaInversaUniform = shader->getUniform ( "matrizMVit" );
                    glm::mat4 matrizMVit = glm::transpose(glm::inverse(matrizModeladoVision)); // Traspuesta de la inversa de la matriz de modelado-vision
                    glUniformMatrix4fv ( matrizTraspuetaInversaUniform, 1, GL_FALSE, glm::value_ptr ( matrizMVit ) );
                }


                // Obtenemos las uniformes generales del Shader
                unsigned int matrizVistaUniform = shader->getUniform ( "matrizModeladoVision" );
                unsigned int matrizProyeccionUniform = shader->getUniform ( "matrizModeladoComposicion" );

                // Obtenemos las uniformes de materiales
                unsigned int componenteAmbiente = shader->getUniform ( "Ka" );
                unsigned int coeficienteDifuso = shader->getUniform ( "Ks" );
                unsigned int intensidadEspecular = shader->getUniform ( "Kd" );
                unsigned int brilloUniform = shader->getUniform ( "brillo" );

                // Cargo materiales del modelo a renderizar
                glm::vec3 Ka = modelos[i]->getColorAmbiente ();
                glm::vec3 Ks = modelos[i]->getExponenteEspecular ();
                glm::vec3 Kd = modelos[i]->getComponenteDifuso ();
                float brillo = modelos[i]->getEspecular();

                // Vinculamos las uniform
                glUniformMatrix4fv ( matrizVistaUniform, 1, GL_FALSE, glm::value_ptr ( matrizModeladoVision ) );
                glUniformMatrix4fv ( matrizProyeccionUniform, 1, GL_FALSE, glm::value_ptr ( matrizModeladoComposicion ) );
                glUniform3fv ( componenteAmbiente, 1, glm::value_ptr ( Ka ) );
                glUniform3fv ( coeficienteDifuso, 1, glm::value_ptr ( Ks ) );
                glUniform3fv ( intensidadEspecular, 1, glm::value_ptr ( Kd ) );
                glUniform1f(brilloUniform, brillo);

                // Activamos la textura y la preparamos
                gestorModelos->activarTexturasModelo(shader->getIdSp(), i);

                renderizarEscena ( modelos[i] );

                // Desactivamos la textura
                gestorModelos->desactivarTexturasModelo(shader->getIdSp(), i);
            }
        }
    }
}

// Asignamos los modelos en VBO
void PAG::Renderer::asignarModeloArrays() {
    if (gestorModelos->getModelosEscena().size() > 0) {
        for (int i = 0; i < gestorModelos->getModelosEscena().size(); i++) {
            for (int j = 0; j < gestorModelos->getModelosEscena()[i]->getNumeroMallas(); j++) {
                PAG::Renderer::GetInstancia()->InicializacionArraysModeloMalla(gestorModelos->getModelosEscena()[i]->getMallaModelo(j).getVertices(),
                                                                               gestorModelos->getModelosEscena()[i]->getMallaModelo(j).getIndices(), gestorModelos->getModelosEscena()[i]->getMallaModelo(j).getTexturas(), gestorModelos->getModelosEscena()[i]->getMallaModelo(j));
            }
        }
    }
}

void PAG::Renderer::InicializacionArraysModeloMalla(std::vector<Vertice> vertices, std::vector<unsigned int> indices, std::vector<Textura> textura, MallaModelo& malla) {
    glGenVertexArrays(1, &idVAO);
    glGenBuffers(1, &idVBO);
    glGenBuffers(1, &idIBO);

    // Aseguramos que los IDS se registran en el modelo tras haber sido usados
    malla.setVao(idVAO);
    malla.setVbo(idVBO);
    malla.setEbo(idIBO);

    glGenVertexArrays(1, malla.getVao());
    glGenBuffers(1, malla.getVbo());
    //glGenBuffers(1, &EBO);

    glBindVertexArray(*malla.getVao());
    glBindBuffer(GL_ARRAY_BUFFER, *malla.getVbo());

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertice), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *malla.getEbo());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)offsetof(Vertice, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)offsetof(Vertice, TexCoords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)offsetof(Vertice, Tangente));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)offsetof(Vertice, Bitangente));

    glBindVertexArray(0);
}

PAG::ShaderHandler *PAG::Renderer::obtenerShaderParaLuz(int indice) {
    switch(lucesEscena[indice]->getTipoLuz()) {
        case TipoLuz::AMBIENTE:
            return shaderAmbiental;
            break;
        case TipoLuz::PUNTUAL:
            return shaderPuntual;
            break;
        case TipoLuz::DIRECCIONAL:
            return shaderDireccional;
            break;
        case TipoLuz::SPOT:
            break;
        default:
            return 0;
    }
    return nullptr;
}

void PAG::Renderer::renderizarEscena(Modelos* modelo) {
// Renderizamos
    for (int j = 0; j < modelo->getNumeroMallas(); j++) {
        if (modelo->isActivoEnEscena()) {
            dibujoModeloMalla(modelo->getMallaModelo(j));
        }
    }
}

void PAG::Renderer::dibujoModeloMalla(MallaModelo &malla) {
    glBindVertexArray(malla.getVaoNor());
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, *malla.getEbo());
    //std::cout << "El VAO id es: " << malla.getVaoNor() << std::endl;
    //std::cout << "El tamaño del vector de indices de la malla es: " << malla.getIndices().size() << std::endl;
    switch(renderizado) {
        case alambre:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
        case relleno:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
    }
    glDrawElements(GL_TRIANGLES, malla.getIndices().size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void PAG::Renderer::activarTextura(GLuint idTextura, GLuint idSP) {
    // Activa el texto unit 0
    glActiveTexture(GL_TEXTURE0);
    // Vincula la textura al texto unit 0
    glBindTexture(GL_TEXTURE_2D, idTextura);
    // Pasa el valor del sampler uniform al shader
    glUniform1i(glGetUniformLocation(idSP, "muestreador"), 0);
}

void PAG::Renderer::desactivarTextura(GLuint idTextura, GLuint idSP) {
    // Desactiva la textura
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void PAG::Renderer::setTipoRenderizadoAlambre() {
    renderizado = alambre;
    actualizarSubrutinasShaders();
}

void PAG::Renderer::setTipoRenderizadoRelleno() {
    renderizado = relleno;
    actualizarSubrutinasShaders();
}

void PAG::Renderer::setTipoRenderizadoRellenoMapeadoNormal() {
    renderizado = rellenoNormales;
    actualizarSubrutinasShaders();
}

void PAG::Renderer::setTipoCalculoColorMaterial() {
    modoCalculoColor = material;
    actualizarSubrutinasShaders();
}

void PAG::Renderer::setTipoCalculoColorTextura() {
    modoCalculoColor = textura;
    actualizarSubrutinasShaders();
}

/**
 * @brief Al cambiar de subrutina, debemos asegurarnos de que se reinicializa el vector de indices de los shaders para evitar problemas.
 * Se asegura de que los índices de las subrutinas activadas se corresponden.
 * @post Los shaders han actualizado sus índices de subrutinas y están listos para ser usados en renderizado.
 */
void PAG::Renderer::actualizarSubrutinasShaders() {

    // Vaciamos los índices de subrutinas
    shaderAmbiental->vaciarIndicesSubrutinas();
    shaderPuntual->vaciarIndicesSubrutinas();
    shaderDireccional->vaciarIndicesSubrutinas();

    switch (modoCalculoColor) {
        case material:
            shaderPuntual->setearSubrutina("uniformEleccionColor", "colorMaterial", GL_FRAGMENT_SHADER);
            shaderAmbiental->setearSubrutina("uniformEleccionColor", "colorMaterial", GL_FRAGMENT_SHADER);
            shaderDireccional->setearSubrutina("uniformEleccionColor", "colorMaterial", GL_FRAGMENT_SHADER);
            break;
        case textura:
            shaderPuntual->setearSubrutina("uniformEleccionColor", "colorTextura", GL_FRAGMENT_SHADER);
            shaderAmbiental->setearSubrutina("uniformEleccionColor", "colorTextura", GL_FRAGMENT_SHADER);
            shaderDireccional->setearSubrutina("uniformEleccionColor", "colorTextura", GL_FRAGMENT_SHADER);
            break;

    }

    switch (renderizado) {
        case relleno:
            shaderPuntual->setearSubrutina("uniformColorElegido", "colorModoLuz", GL_FRAGMENT_SHADER);
            shaderAmbiental->setearSubrutina("uniformColorElegido", "colorModoLuz", GL_FRAGMENT_SHADER);
            shaderDireccional->setearSubrutina("uniformColorElegido", "colorModoLuz", GL_FRAGMENT_SHADER);
            break;
        case alambre:
            shaderPuntual->setearSubrutina("uniformColorElegido", "colorModoAlambre", GL_FRAGMENT_SHADER);
            shaderAmbiental->setearSubrutina("uniformColorElegido", "colorModoAlambre", GL_FRAGMENT_SHADER);
            shaderDireccional->setearSubrutina("uniformColorElegido", "colorModoAlambre", GL_FRAGMENT_SHADER);
            break;
        case rellenoNormales:
            shaderPuntual->setearSubrutina("uniformColorElegido", "colorModoLuzTexturaNormal", GL_FRAGMENT_SHADER);
            shaderAmbiental->setearSubrutina("uniformColorElegido", "colorModoLuzTexturaNormal", GL_FRAGMENT_SHADER);
            shaderDireccional->setearSubrutina("uniformColorElegido", "colorModoLuzTexturaNormal", GL_FRAGMENT_SHADER);
            break;
    }
}

void PAG::Renderer::inicializarShaders() {
    // Inicialización shaders
    shaderAmbiental = new ShaderHandler();
    shaderAmbiental->creaShaderProgram("pag03-vs.glsl" ,"pag03-fs.glsl");
    shaderPuntual = new ShaderHandler();
    shaderPuntual->creaShaderProgram("pag03-vs-luzPuntual.glsl", "pag03-fs-puntualLightShader.glsl");
    shaderDireccional = new ShaderHandler();
    shaderDireccional->creaShaderProgram("pag03-vs-luzDireccional.glsl", "pag03-fs-directionalLightShader.glsl");
}

void PAG::Renderer::crearLuzPuntual(glm::vec3 colorDifuso, glm::vec3 colorEspecular, glm::vec3 posicion) {
    PAG::TipoLuz tipoLuz2 = PAG::TipoLuz::PUNTUAL;
    PAG::Luz* luzPuntual = new PAG::Luz(tipoLuz2, colorDifuso, colorEspecular, posicion);
    lucesEscena.push_back(luzPuntual);
}

void PAG::Renderer::crearluzDireccional(glm::vec3 colorDifuso, glm::vec3 colorEspecular, glm::vec3 direccion) {
    PAG::TipoLuz tipoLuz3 = PAG::TipoLuz::DIRECCIONAL;
    PAG::Luz* luzDireccional = new PAG::Luz(tipoLuz3, colorDifuso,
                                            colorEspecular, glm::vec3(5.0, 5.0, 4.0), direccion);
    lucesEscena.push_back(luzDireccional);
}

PAG::Camara *PAG::Renderer::getCamara() const {
    return camara;
}
