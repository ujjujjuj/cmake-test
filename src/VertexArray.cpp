#include "VertexArray.h"

#include <GL/glew.h>

#include <vector>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray() {
    GLCall(glGenVertexArrays(1, &m_RendererID));
    GLCall(glBindVertexArray(m_RendererID));
}
VertexArray::~VertexArray() {
}

void VertexArray::AddBuffer(const VertexBuffer& vb, VertexBufferLayout& layout) {
    vb.Bind();
    const std::vector<VertexBufferElement>& elements = layout.GetElements();
    for (int i = 0; i < elements.size(); i++) {
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalized ? 1 : 0, layout.GetStride(), reinterpret_cast<void*>(elements[i].offset)));
    }
    vb.Unbind();
}

void VertexArray::Bind() {
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() {
    GLCall(glBindVertexArray(0));
}