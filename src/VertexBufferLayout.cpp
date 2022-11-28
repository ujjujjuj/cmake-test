#include "VertexBufferLayout.h"

#include <iostream>
#include <stdexcept>

VertexBufferLayout::VertexBufferLayout() : m_Stride(0) {
}

unsigned int VertexBufferLayout::GetStride() const {
    return m_Stride;
}

const std::vector<VertexBufferElement> &VertexBufferLayout::GetElements() const {
    return m_Elements;
}

void VertexBufferLayout::Push(unsigned int type, unsigned int count) {
    unsigned int size = 0;
    switch (type) {
        case GL_FLOAT:
        case GL_INT:
        case GL_UNSIGNED_INT:
            size += 4 * count;
            break;
        case GL_SHORT:
        case GL_UNSIGNED_SHORT:
            size += 2 * count;
            break;
        case GL_UNSIGNED_BYTE:
        case GL_BYTE:
            size += 1 * count;
            break;
        default:
            throw std::runtime_error("Type not supported for Vertex Buffer Layout!\n");
            break;
    }
    m_Elements.push_back({type, count, m_Stride, GL_FALSE});
    m_Stride += size;
}
