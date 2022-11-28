#include "Shader.h"

#include <GL/glew.h>

#include <fstream>
#include <sstream>
#include <stdexcept>

#include "Renderer.h"

Shader::Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
    GLCall(m_RendererID = glCreateProgram());

    std::string vsSource = ReadFile(vertexShaderPath);
    std::string fsSource = ReadFile(fragmentShaderPath);

    unsigned int vs = CompileShader(vsSource, GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(fsSource, GL_FRAGMENT_SHADER);

    GLCall(glAttachShader(m_RendererID, vs));
    GLCall(glAttachShader(m_RendererID, fs));
    GLCall(glLinkProgram(m_RendererID));
    GLCall(glValidateProgram(m_RendererID));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
}

Shader::~Shader() {}

std::string Shader::ReadFile(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file " + filePath);
    }

    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

unsigned int Shader::CompileShader(const std::string &src, unsigned int type) {
    GLCall(unsigned int id = glCreateShader(type));
    const char *src_c = src.c_str();
    GLCall(glShaderSource(id, 1, &src_c, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int len;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len));
        char message[len];
        GLCall(glGetShaderInfoLog(id, len, &len, message));
        throw std::runtime_error("Failed to compile shader: " + std::string(message) + "\n");
    }

    return id;
}

int Shader::GetUniformLocation(const std::string &uName) {
    GLCall(int uColorLoc = glGetUniformLocation(m_RendererID, uName.c_str()));
    if (uColorLoc == -1) {
        throw std::runtime_error("Uniform " + uName + " does not exist in this program!\n");
    }
    return uColorLoc;
}

void Shader::SetUniform4f(const std::string &uName, float v0, float v1, float v2, float v3) {
    if (m_UniformLocationCache.find(uName) == m_UniformLocationCache.end()) {
        m_UniformLocationCache[uName] = GetUniformLocation(uName);
    }
    GLCall(glUniform4f(m_UniformLocationCache[uName], v0, v1, v2, v3));
}

void Shader::Bind() {
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() {
    GLCall(glUseProgram(0));
}