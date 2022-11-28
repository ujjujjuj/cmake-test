#pragma once

#include <GL/glew.h>

#include <stdexcept>
#include <vector>

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned int offset;
    bool normalized;
};

class VertexBufferLayout {
   private:
    unsigned int m_Stride;
    std::vector<VertexBufferElement> m_Elements;

   public:
    VertexBufferLayout();
    const std::vector<VertexBufferElement> &GetElements() const;
    unsigned int GetStride() const;
    void Push(unsigned int type, unsigned int count);
};