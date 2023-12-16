//
// Created by carlo on 2023/10/30.
//

#include "Modelos.h"

PAG::MallaModelo &PAG::Modelos::getMallaModelo(int indice) {
    return malla[indice]->obtenerMalla();
}

PAG::Modelos::~Modelos() {
    for (int i = 0; i < malla.size(); i++) {
        delete malla[i];
        malla[i] = nullptr;
    }
    malla.clear();
}

const int PAG::Modelos::getNumeroMallas() {
    return malla.size();
}

//TODO 真空モデルを付けないようにロッドしなければならないモデルが無ければmodelosというクラスに放送する！！
void PAG::Modelos::cargarModelo(std::string path) {
    Assimp::Importer importador;
    const aiScene* escena = nullptr; // Inicializa con nullptr
    try {
        escena = importador.ReadFile(path, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_GenSmoothNormals);

        if (!escena || escena->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !escena->mRootNode) {
            std::cout << "ERROR::ASSIMP::CARGA::MODELO::" << importador.GetErrorString() << std::endl;
            return;
        }

        directorio = path.substr(0, path.find_last_of('/'));
        procesarNodo(escena->mRootNode, escena);
    } catch (const std::exception& e) {
        std::cerr << "Excepción al cargar el modelo: " << e.what() << std::endl;
    }
}

void PAG::Modelos::procesarNodo(aiNode *node, const aiScene *scene) {
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        malla.push_back(procesarMalla(mesh, scene));
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        procesarNodo(node->mChildren[i], scene);
    }
}

PAG::MallaModelo* PAG::Modelos::procesarMalla(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertice> vertices;
    std::vector<unsigned int> indices;
    std::vector<Textura> texturas;

    // Procesar vértices
    for(int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertice vertice;
        // process vertice positions, normals and texture coordinates
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertice.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertice.Normal = vector;

        // Cargamos las texturas
        if(mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertice.TexCoords = vec;
        }
        else {
            vertice.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertice);
    }

    // Procesar índices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    MallaModelo* malla = new MallaModelo(vertices, indices, texturas);
    return malla;
}

const glm::mat4 &PAG::Modelos::getMatrizModeladoModelo() const {
    return matrizModeladoModelo;
}

void PAG::Modelos::setMatrizModeladoModelo(const glm::mat4 &matrizModeladoModelo) {
    Modelos::matrizModeladoModelo = matrizModeladoModelo;
}

bool PAG::Modelos::isActivoEnEscena() const {
    return activoEnEscena;
}

void PAG::Modelos::setActivoEnEscena(bool activoEnEscena) {
    Modelos::activoEnEscena = activoEnEscena;
}

GLuint PAG::Modelos::getIdSp() const {
    return idSP;
}

void PAG::Modelos::setIdSp(GLuint idSp) {
    idSP = idSp;
}

glm::vec3 PAG::Modelos::getColorAmbiente() const {
    return colorAmbiente;
}

void PAG::Modelos::setColorAmbiente(glm::vec3 colorAmbiente) {
    Modelos::colorAmbiente = colorAmbiente;
}

glm::vec3 PAG::Modelos::getComponenteDifuso() const {
    return componenteDifuso;
}

void PAG::Modelos::setComponenteDifuso(glm::vec3 componenteDifuso) {
    Modelos::componenteDifuso = componenteDifuso;
}

glm::vec3 PAG::Modelos::getExponenteEspecular() const {
    return exponenteEspecular;
}

void PAG::Modelos::setExponenteEspecular(glm::vec3 exponenteEspecular) {
    Modelos::exponenteEspecular = exponenteEspecular;
}

float PAG::Modelos::getEspecular() const {
    return especular;
}

void PAG::Modelos::setEspecular(float especular) {
    Modelos::especular = especular;
}

PAG::Modelos::Modelos(const char *path, glm::mat4 matrizModelado, float brillo, glm::vec3 colorAmbiental,
                      glm::vec3 componenteDifuso, glm::vec3 exponenteEspecular) {
    activoEnEscena = true;
    this->matrizModeladoModelo = matrizModelado;
    cargarModelo(path);

    this->especular = brillo;
    this->colorAmbiente = colorAmbiental;
    this->componenteDifuso = componenteDifuso;
    this->exponenteEspecular = exponenteEspecular;
}

GLuint PAG::Modelos::getIdTextura() const {
    return idTextura;
}

void PAG::Modelos::setIdTextura(GLuint idTextura) {
    Modelos::idTextura = idTextura;
}

