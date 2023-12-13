#version 410

//in vec4 colorFragmentoIn;
out vec4 colorFragmento;

uniform vec3 direccion;
uniform vec3 Id;
uniform vec3 Is;

uniform vec3 Ka;
uniform vec3 Ks;
uniform vec3 Kd;

vec3 brillo;
uniform sampler2D muestreador;   // Sampler para comunicar con la unidad de textura

//subroutine vec4 calcularColor();
//subroutine uniform calcularColor colorElegido;

in salidaVS {
    vec3 posicionV;
    vec3 normalV;
    vec2 cTexturaV;
} entrada;

vec3 n = normalize(entrada.normalV);

vec4 calcularFuenteLuminosaDireccional (vec4 color) {
    vec3 l = normalize(-direccion);
    vec3 v = normalize(-entrada.posicionV);
    vec3 r = reflect(-l, n);

    vec3 difusa = (vec3(color) * Id * Kd * max(dot(l, n), 0.0));
    vec3 especular = (Ks * Is * pow(max(dot(r, v), 0.0), 32));

    vec3 suma = (difusa + especular);
	return vec4(suma, 1.0);
}

// Definición de subrutinas
subroutine vec4 elegirColor();
subroutine uniform elegirColor uniformEleccionColor;
subroutine vec4 calcularColor(vec4 colorDePartida);
subroutine uniform calcularColor uniformColorElegido;

subroutine(elegirColor)
vec4 colorTextura() {
    vec3 color = texture(muestreador, entrada.cTexturaV).rgb;
    return vec4(color, 1);
}

subroutine(elegirColor)
vec4 colorMaterial() {
    return vec4(1.0, 1.0, 1.0, 1.0); // Color que no influye y permite que el material sea solo el de la luz
}

subroutine( calcularColor )
vec4 colorModoAlambre (vec4 colorDePartida) {
    return colorDePartida;
}

subroutine( calcularColor )
vec4 colorModoLuz (vec4 colorDePartida) {
    return calcularFuenteLuminosaDireccional(colorDePartida);
    //return vec4(0,0,0,1);
}

void main () {
    colorFragmento = uniformColorElegido(uniformEleccionColor());
}
