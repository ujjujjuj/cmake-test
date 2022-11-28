#include "IndexBuffer.h"

#include <GL/glew.h>

#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) {
    m_Count = count;
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_READ));
}

IndexBuffer::~IndexBuffer() {
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

unsigned int IndexBuffer::GetCount() {
    return m_Count;
}

void IndexBuffer::Bind() {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}