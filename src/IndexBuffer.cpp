// Created by gruba on 3/23/2024.
//

#include "IndexBuffer.h"
#include <GL/glew.h>
#include "Renderer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int count): m_Count(count) {
    GlCall(glGenBuffers(1, &m_RendererId));
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
    GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(GLuint), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    GlCall(glDeleteBuffers(1, &m_RendererId));
}

void IndexBuffer::bind() const {
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
}

void IndexBuffer::unbind() const {
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
