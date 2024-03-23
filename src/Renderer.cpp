//
// Created by gruba on 3/23/2024.
//

#include "Renderer.h"
#include <iostream>
#include <GL/glew.h>

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
