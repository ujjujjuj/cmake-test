#version 330 core

out vec4 fragColor;
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 vertexColor;

void main() {
    gl_Position = position;
    fragColor = vertexColor;
}