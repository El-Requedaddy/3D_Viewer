#version 410

layout (location = 0) in vec3 posicion;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textCoords;
layout (location = 3) in vec3 tangente;
layout (location = 4) in vec3 bitangente;

//out vec4 colorFragmentoIn;

uniform mat4 matrizModeladoVision;
uniform mat4 matrizModeladoComposicion;
uniform mat4 matrizMVit; // Traspuesta de la inversa de matrizMV
uniform vec3 luzDir;

out salidaVS {
	vec3 posicionV;
	vec3 normalV;
	vec2 cTexturaV;
	vec3 posicionTg;
	vec3 dirLuzTg;
} salida;

void main () {
	vec3 normal = vec3(matrizModeladoVision * vec4(normal, 0.0));
	vec3 normalMV = normalize ( vec3 ( matrizMVit * vec4 ( normal, 0 ) ) );
	vec3 tangenteMV = normalize ( vec3 ( matrizMVit * vec4 ( tangente, 0 ) ) );
	vec3 bitangenteMV = normalize ( cross ( normalMV, tangenteMV ) );
	mat3 TBN = transpose ( mat3 ( tangenteMV, bitangenteMV, normalMV ) );
	salida.posicionTg = TBN * vec3 ( matrizModeladoVision * vec4 ( luzDir, 1 ) );
	salida.dirLuzTg = TBN * luzDir;

	salida.normalV = normal;
	salida.posicionV = vec3(matrizModeladoVision * vec4(posicion, 1.0));
	salida.cTexturaV = textCoords;   // Las coordenadas de textura se pasan tal cual al fragment shader
	gl_Position = matrizModeladoComposicion * vec4(posicion, 1.0);
}
