#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>
#include <string>

#include "IndexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

const int windowWidth = 600;
const int windowHeight = 600;

int main(void) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!\n";
        exit(1);
    }
    GLFWwindow* window = glfwCreateWindow(600, 600, "OpenGL Window", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        std::cerr << "Failed to create a window!\n";
        exit(1);
    }
    glfwMakeContextCurrent(window);

    unsigned int glewError = glewInit();
    if (glewError != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW!\n";
        exit(1);
    }

    glfwWindowHint(GL_MAJOR_VERSION, 3);
    glfwWindowHint(GL_MINOR_VERSION, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSwapInterval(1);

    float vertices[] = {
        -0.5, -0.5, 1, 0, 0,
        0.5, -0.5, 0, 1, 0,
        0, 0.5, 0, 0, 1};
    unsigned int indexes[] = {
        0, 1, 2};

    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.Push(GL_FLOAT, 2);
    layout.Push(GL_FLOAT, 3);
    IndexBuffer ib(indexes, 3);
    va.AddBuffer(vb, layout);

    Shader shader("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");
    shader.Bind();
    float ctr = 0;
    bool isPos = true;
    while (!glfwWindowShouldClose(window)) {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        shader.Bind();
        va.Bind();

        GLCall(glClearColor(0.0, 0.0, 0.0, 1.0));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        ctr += 0.01 * (isPos ? 1 : -1);
        if (ctr > 1 || ctr < 0) isPos = !isPos;

        GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

        shader.Unbind();
        va.Unbind();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}