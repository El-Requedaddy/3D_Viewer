#version 410

layout (location = 0) in vec3 posicion;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textCoords;

//out vec4 colorFragmentoIn;

uniform mat4 matrizModeladoVision;
uniform mat4 matrizModeladoComposicion;

out salidaVS {
	vec3 posicionV;
	vec3 normalV;
	vec2 cTexturaV;
} salida;

void main () {
	salida.normalV = normal;
	salida.posicionV = vec3(matrizModeladoVision * vec4(posicion, 1.0));
	salida.cTexturaV = textCoords;   // Las coordenadas de textura se pasan tal cual al fragment shader
	gl_Position = matrizModeladoComposicion * vec4(posicion, 1.0);
}
