#version 330 core

out vec4 color;
uniform vec4 u_Color;

varying vec4 fragColor;

void main() {
    color = fragColor;
}
