#pragma once

#include <GL/glew.h>

#include <iostream>
#include <string>

#define ASSERT(x)                          \
    if (!(x)) {                            \
        std::cerr << "Assertion failed\n"; \
        exit(1);                           \
    }
// #ifdef DEBUG_MODE
 #define GLCall(x)   \
    GLClearError(); \
    x;              \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
// #else
// #define GLCall(x) std::cout << "nigger\n";
// #endif

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
};