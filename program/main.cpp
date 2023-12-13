#include <iostream>
#include <cstdlib>
// IMPORTANTE: El include de GLEW debe estar siempre ANTES de el de GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "Luz.h"

//Variables necesarias para distintas aplicaciones
float rojo = 0;
float azul = 0;
float verde = 0;
float rgb[3] = {rojo, azul, verde};
float velocidadRaton = 3.0f;
bool clickIzquierdoMantenido = false;

// - Esta función callback será llamada cada vez que el área de dibujo
// OpenGL deba ser redibujada.
void window_refresh_callback ( GLFWwindow *window )
{
    PAG::Renderer::GetInstancia()->Refrescar();

// - GLFW usa un doble buffer para que no haya parpadeo. Esta orden
// intercambia el buffer back (que se ha estado dibujando) por el
// que se mostraba hasta ahora front. Debe ser la última orden de
// este callback
    glfwSwapBuffers ( window ); // Esto pasaría a formar parte de la clase Renderer
    std::cout << "Refresh callback called" << std::endl;
}

// - Esta función callback será llamada cada vez que se cambie el tamaño
// del área de dibujo OpenGL.
void framebuffer_size_callback ( GLFWwindow *window, int width, int height )
{ PAG::Renderer::GetInstancia()->SetViewport(0, 0, width, height);
    std::cout << "Resize callback called" << std::endl;
}

// - Esta función callback será llamada cada vez que se pulse una tecla
// dirigida al área de dibujo OpenGL.
void key_callback ( GLFWwindow *window, int key, int scancode, int action, int mods )
{ if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
    { PAG::Renderer::GetInstancia()->SetWindowShouldClose(window);
    }
    std::cout << "Key callback called" << std::endl;


    // Movimientos de camara con teclas
    if (key == GLFW_KEY_UP && action == GLFW_PRESS){
        PAG::Renderer::GetInstancia()->movimientoTeclasCamara(GLFW_KEY_UP);
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS){
        PAG::Renderer::GetInstancia()->movimientoTeclasCamara(GLFW_KEY_DOWN);
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
        PAG::Renderer::GetInstancia()->movimientoTeclasCamara(GLFW_KEY_RIGHT);
    }
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS){
        PAG::Renderer::GetInstancia()->movimientoTeclasCamara(GLFW_KEY_LEFT);
    }
    if (key == GLFW_KEY_P && action == GLFW_PRESS){ // Panorámica Izquierda
        PAG::Renderer::GetInstancia()->movimientoTeclasCamara(GLFW_KEY_P);
    }
    if (key == GLFW_KEY_C && action == GLFW_PRESS){ // Cabeceo Izquierda
        PAG::Renderer::GetInstancia()->movimientoTeclasCamara(GLFW_KEY_C);
    }
    if (key == GLFW_KEY_O && action == GLFW_PRESS){ // Panorámica Derecha
        PAG::Renderer::GetInstancia()->movimientoTeclasCamara(GLFW_KEY_O);
    }
    if (key == GLFW_KEY_X && action == GLFW_PRESS){ // Cabeceo Derecha
        PAG::Renderer::GetInstancia()->movimientoTeclasCamara(GLFW_KEY_X);
    }

    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        // Añadimos Modelos
        PAG::Renderer::GetInstancia()->anadirEliminarModelos(false);
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        // Quitamos modelo
        PAG::Renderer::GetInstancia()->anadirEliminarModelos(true);
    }

    // Cambio de modo de visualización
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        // Con la tecla Q ponemos modo de relleno en la visualización
        PAG::Renderer::GetInstancia()->setTipoRenderizadoRelleno();
    }
    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        // Con la tecla E ponemos modo de alambre en la visualización
        PAG::Renderer::GetInstancia()->setTipoRenderizadoAlambre();
    }

    // Cambio de color de modelos
    if (key == GLFW_KEY_T && action == GLFW_PRESS) {
        // Con la tecla T ponemos modo de color de textura en la visualización
        PAG::Renderer::GetInstancia()->setTipoCalculoColorTextura();
    }
    if (key == GLFW_KEY_Y && action == GLFW_PRESS) {
        // Con la tecla Y ponemos modo de color de material en la visualización
        PAG::Renderer::GetInstancia()->setTipoCalculoColorMaterial();
    }

}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    PAG::Renderer::GetInstancia()->movimientoRatonCamara(xpos, ypos, clickIzquierdoMantenido);
    std::cout << "Movimiento de ratón registrado en pantalla" << "\n";
}

// - Esta función callback será llamada cada vez que se pulse algún botón
// del ratón sobre el área de dibujo OpenGL.
void mouse_button_callback ( GLFWwindow *window, int button, int action, int mods )

{

    if ( action == GLFW_PRESS )
    {
        if (button == 0) {
            clickIzquierdoMantenido = true;
            std::cout << "Click presionado" << std::endl;
        }
        std::cout << "Pulsado el boton: " << button << std::endl;
    }
    else if ( action == GLFW_RELEASE )
    {
        if (button == 0 && clickIzquierdoMantenido)
            clickIzquierdoMantenido = false;

        std::cout << "Soltado el boton: " << button << std::endl;
    }
}

//EJERCICIO 1 SCROLL CALLBACK
// - Esta función callback será llamada cada vez que se mueva la rueda
// del ratón sobre el área de dibujo OpenGL.
void scroll_callback ( GLFWwindow *window, double xoffset, double yoffset )
{
    //Número que suma o resta al RGB
    float adicion = 0.01;

    // Existe un vector RGB que contiene el valor de cada uno de los colores del RGB
    // Dicho vector se recorre para ir aumentando o decreciendo el color

    // Este bucle ocurre al subir la rueda del raton hacia arriba. Se aumenta cada componente RGB
    // Se comprueba si el componente RGB es menor que uno, si fuese así se puede incrementar, en caso de que sea igual a 1
    // se aumenta el siguiente componente RGB, así hasta llegar a 1 en el R, G y B.
    if (yoffset == 1) {
        for (int i = 0; i < 3; i++) {
            if (rgb[i] < 1) {
                rgb[i] += adicion;
                break;
            }
        }
        // Este else es el opuesto al anterior, reduciendo el valor de los componentes RGB, empezando
        // por el B hasta el R.
        // En caso de que el componente RGB sea menor que 0.01 se pasará al siguiente, de modo que si bajásemos lo máximo posible
        // tendremos los R, G y B a 0
    } else if (yoffset == -1) {
        for (int i = 2; i > -1; i--) {
            if (rgb[i] > 0.01) {
                rgb[i] -= adicion;
                break;
            }
        }
    }

    // No requerimos de CLAMP dado que al dividir los incrementos y decrementos en los 3 componentes RGB
    // nunca podremos seguir más alla de las condiciones establecidas en el condicional anterior
    PAG::Renderer::GetInstancia()->RefrescarColor(rgb[0], rgb[1], rgb[2], 1.0);
    PAG::Renderer::GetInstancia()->Refrescar();
    glfwSwapBuffers ( window );

}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    // Mando los parámetros de pantalla al renderer para que los tenga en cuenta
    PAG::Renderer::GetInstancia()->setAnchuraPantalla(width);
    PAG::Renderer::GetInstancia()->setAlturaPantalla(height);
}

int main() {

    std::cout << "Starting Application PAG - Prueba 01" << std::endl;
    // - Inicializa GLFW. Es un proceso que sólo debe realizarse una vez en la aplicación
    if ( glfwInit () != GLFW_TRUE )
    { std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // - Definimos las características que queremos que tenga el contexto gráfico
    // OpenGL de la ventana que vamos a crear. Por ejemplo, el número de muestras o el
    // modo Core Profile.
    glfwWindowHint ( GLFW_SAMPLES, 4 ); // - Activa antialiasing con 4 muestras.
    glfwWindowHint ( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE ); // - Esta y las 2
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MAJOR, 4 ); // siguientes activan un contexto
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MINOR, 1 ); // OpenGL Core Profile 4.1.

    // - Definimos el puntero para guardar la dirección de la ventana de la aplicación y
    // la creamos
    GLFWwindow *window;
    // - Tamaño, título de la ventana, en ventana y no en pantalla completa,
    // sin compartir recursos con otras ventanas.
    window = glfwCreateWindow ( 1024, 576, "PAG Introduction", nullptr, nullptr );
    PAG::Renderer::GetInstancia()->setAnchuraPantalla(1024);
    PAG::Renderer::GetInstancia()->setAlturaPantalla(576);

    // - Comprobamos si la creación de la ventana ha tenido éxito.
    if ( window == nullptr )
    { std::cout << "Failed to open GLFW window" << std::endl;
        glfwTerminate (); // - Liberamos los recursos que ocupaba GLFW.
        return -2;
    }

    // - Hace que el contexto OpenGL asociado a la ventana que acabamos de crear pase a
    // ser el contexto actual de OpenGL para las siguientes llamadas a la biblioteca
    glfwMakeContextCurrent ( window );

    // - Ahora inicializamos GLEW.
    // IMPORTANTE: GLEW debe inicializarse siempre DESPUÉS de que se haya
    // inicializado GLFW y creado la ventana
    glewExperimental = true;
    if ( glewInit() != GLEW_OK )
    { std::cout << "Failed to initialize GLEW" << std::endl;
        glfwDestroyWindow ( window );
        glfwTerminate (); // - Liberamos los recursos que ocupaba GLFW.
        return -3;
    }

    // - Interrogamos a OpenGL para que nos informe de las propiedades del contexto
    // 3D construido.
    std::cout << glGetString ( GL_RENDERER ) << std::endl
              << glGetString ( GL_VENDOR ) << std::endl
              << glGetString ( GL_VERSION ) << std::endl
              << glGetString ( GL_SHADING_LANGUAGE_VERSION ) << std::endl;

    // - Registramos los callbacks que responderán a los eventos principales
    glfwSetWindowRefreshCallback ( window, window_refresh_callback );
    glfwSetFramebufferSizeCallback ( window, framebuffer_size_callback );
    glfwSetKeyCallback ( window, key_callback );
    glfwSetMouseButtonCallback ( window, mouse_button_callback );
    glfwSetScrollCallback ( window, scroll_callback );

    // Llama al método inicializaOpenGL para configurar el estado inicial de OpenGL
    PAG::Renderer::GetInstancia()->inicializaOpenGL();
    PAG::Renderer::GetInstancia()->inicializarShaders();

    // Inicializamos los shaders y las luces. Este método inicializa una luz y asigna un shader correspondiente.
    PAG::TipoLuz tipoLuz = PAG::TipoLuz::AMBIENTE;
    PAG::Luz* luzAmbiental = new PAG::Luz(tipoLuz, glm::vec3(0.2, 0.2, 0.2));
    PAG::Renderer::GetInstancia()->anadirLuces(luzAmbiental);

    PAG::TipoLuz tipoLuz2 = PAG::TipoLuz::PUNTUAL;
    PAG::Luz* luzPuntual = new PAG::Luz(tipoLuz2, glm::vec3(0.8, 0.6, 1.0), glm::vec3(1.0, 0.6, 1.0), glm::vec3(0.0, 3.0, 0.0));
    PAG::Renderer::GetInstancia()->anadirLuces(luzPuntual);

    PAG::Luz* luzPuntual2 = new PAG::Luz(tipoLuz2, glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(5.0, 2.0, 5.0));
    PAG::Renderer::GetInstancia()->anadirLuces(luzPuntual2);
    //PAG::Renderer::GetInstancia()->inicializacionShadersYLuces("pag03-fs-puntualLightShader.glsl.txt");

    PAG::TipoLuz tipoLuz3 = PAG::TipoLuz::DIRECCIONAL;
    PAG::Luz* luzDireccional = new PAG::Luz(tipoLuz3, glm::vec3(0.4, 0.6, 0.7), glm::vec3(1.0, 0.6, 0.5), glm::vec3(5.0, 5.0, 4.0), glm::vec3(5.0, 5.0, 4.0));
    PAG::Renderer::GetInstancia()->anadirLuces(luzDireccional);

    // Inicializamos e indicamos las subrutinas a usar
    PAG::Renderer::GetInstancia()->actualizarSubrutinasShaders();

    // Creamos la cámara
    PAG::Renderer::GetInstancia()->seteoCamara();

//    char *path = "Modelos/AnimeModelo.obj";
    glm::mat4 matrizModelado = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
    //   matrizModelado = glm::scale(matrizModelado, glm::vec3(0.01f));
//    PAG::Renderer::GetInstancia()->crearModelo(path, matrizModelado);

    /*
    std::string path2 = "Modelos/Mandalorian.obj";
    matrizModelado = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    PAG::Renderer::GetInstancia()->crearModelo(path2.c_str(), matrizModelado, "");
    */

    std::string path3 = "Modelos/dado.obj";
    matrizModelado = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    PAG::Renderer::GetInstancia()->crearModelo(path3.c_str(), matrizModelado, "Texturas/dado.png");

    std::string path4 = "Modelos/vacaSinNormales.obj";
    matrizModelado = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    matrizModelado = glm::scale(matrizModelado, glm::vec3(0.95f));
    PAG::Renderer::GetInstancia()->crearModelo(path4.c_str(), matrizModelado, "Texturas/spot_texture.png");

      /*
    std::string path6 = "Modelos/NeonSushi.obj";
    matrizModelado = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 0.0f, -1.0f));
    matrizModelado = glm::scale(matrizModelado, glm::vec3(0.01f));
    PAG::Renderer::GetInstancia()->crearModelo(path6.c_str(), matrizModelado, "");

    std::string path7 = "Modelos/SAOModel.obj";
    matrizModelado = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    matrizModelado = glm::scale(matrizModelado, glm::vec3(0.008f));
    PAG::Renderer::GetInstancia()->crearModelo(path7.c_str(), matrizModelado, "");
    */

    // - Ciclo de eventos de la aplicación. La condición de parada es que la
    // ventana principal deba cerrarse. Por ejemplo, si el usuario pulsa el
    // botón de cerrar la ventana (la X).
    while ( !glfwWindowShouldClose ( window ) )
    {   // - Obtiene y organiza los eventos pendientes, tales como pulsaciones
        // de teclas o de ratón, etc. Siempre al final de cada iteración del
        // ciclo de eventos y después de glfwSwapBuffers ( window );

        PAG::Renderer::GetInstancia()->Refrescar();
        //PAG::Renderer::GetInstancia()->renderizarModelos();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // - Una vez terminado el ciclo de eventos, liberar recursos, etc.
    std::cout << " 「pag prueba」の仕組み終了　" << std::endl;

    glfwDestroyWindow ( window ); // - Cerramos y destruimos la ventana de la aplicación.
    window = nullptr;
    glfwTerminate (); // - Liberamos los recursos que ocupaba GLFW.

    // - Esta llamada es para impedir que la consola se cierre inmediatamente tras la
    // ejecución y poder leer los mensajes
    getchar ();
}