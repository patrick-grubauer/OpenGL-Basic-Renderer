//
// Created by gruba on 3/23/2024.
//

#include "VertexArray.h"

#include "../Renderer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray() {
    GlCall(glGenVertexArrays(1,&m_RenderId));
}

VertexArray::~VertexArray() {
    GlCall(glDeleteVertexArrays(1,&m_RenderId));
}

void VertexArray::bind() const {
    GlCall(glBindVertexArray(m_RenderId));
}

void VertexArray::unbind() const {
    GlCall(glBindVertexArray(0));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
    bind();
    vb.bind();
    const auto& elements = layout.getElements();
    unsigned int offset = 0;
    for (int i = 0; i < elements.size(); ++i) {
        const auto& element = elements[i];
        GlCall(glEnableVertexAttribArray(i));
        GlCall(
            glVertexAttribPointer(i, element.count,element.type, element.normalized, layout.getStride(), (GLvoid *)
                offset));
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}
