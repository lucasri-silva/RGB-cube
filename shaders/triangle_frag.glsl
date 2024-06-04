#version 330 core

uniform sampler2D TextureSampler;

in vec2 UV;
in vec3 Color;
out vec4 OutColor;

void main() {
    // Definindo cor via UV
    //OutColor = vec4(UV.x, UV.y, 0.0, 1.0);

	OutColor = vec4(Color, 1.0);
}