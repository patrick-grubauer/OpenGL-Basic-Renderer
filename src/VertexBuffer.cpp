//
// Created by gruba on 3/23/2024.
//

#include "VertexBuffer.h"
#include <GL/glew.h>
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    GlCall(glGenBuffers(1, &m_RendererId));
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
    GlCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
    GlCall(glDeleteBuffers(1, &m_RendererId));
}

void VertexBuffer::bind() const {
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
}

void VertexBuffer::unbind() const {
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
