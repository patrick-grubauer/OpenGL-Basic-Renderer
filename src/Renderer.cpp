//
// Created by gruba on 3/23/2024.
//

#include "Renderer.h"
#include <iostream>
#include <GL/glew.h>

void Renderer::clear() const {
    GlCall(glClear(GL_COLOR_BUFFER_BIT));
}

void GLClearError() {
    while (glGetError());
}

bool GlLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << ") Function:" << function << " File:" << file << ":" << line <<
                std::endl;
        return false;
    }
    return true;
}

void Renderer::drawTriangle() const {
}

void Renderer::drawTest(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
    va.bind();
    ib.bind();
    GlCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr););
}
