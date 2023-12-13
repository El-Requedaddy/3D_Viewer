#version 410

out vec4 colorFragmento;

uniform vec3 luzAmbiental;

uniform vec3 Ka;
uniform vec3 Ks;
uniform vec3 Kd;

uniform sampler2D muestreador; // Sampler para comunicar con la unidad de textura

in salidaVS {
    vec3 posicionV;
    vec3 normalV;
    vec2 cTexturaV;
} entrada;

vec3 n = normalize(entrada.normalV);

vec4 calcularAmbiente(vec4 color) {
    return vec4(vec3(color) * Ka * luzAmbiental, 1.0);
}

// Definición de subrutinas
subroutine vec4 elegirColor();
subroutine uniform elegirColor uniformEleccionColor;
subroutine vec4 calcularColor(vec4 colorDePartida);
subroutine uniform calcularColor uniformColorElegido;

subroutine(elegirColor)
vec4 colorTextura() {
    vec3 texColor = texture(muestreador, entrada.cTexturaV).rgb;
    return vec4(texColor, 1.0);
}

subroutine(elegirColor)
vec4 colorMaterial() {
    return vec4(1.0, 1.0, 1.0, 1.0);
}

subroutine(calcularColor)
vec4 colorModoAlambre(vec4 colorDePartida) {
    return colorDePartida;
    //return calcularAmbiente(colorDePartida);
    //return vec4(0,0,0,1);
}

subroutine(calcularColor)
vec4 colorModoLuz(vec4 colorDePartida) {
    return calcularAmbiente(colorDePartida);
    //return vec4(0,0,0,1);
}

void main () {
    colorFragmento = uniformColorElegido(uniformEleccionColor());
}
