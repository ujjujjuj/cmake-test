#pragma once

#include <string>
#include <unordered_map>

class Shader {
   private:
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocationCache;

   public:
    Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
    ~Shader();

    std::string ReadFile(const std::string &filePath);
    unsigned int CompileShader(const std::string &src, unsigned int type);
    int GetUniformLocation(const std::string &uName);
    void SetUniform4f(const std::string &uName, float v0, float v1, float v2, float v3);
    void Bind();
    void Unbind();
};