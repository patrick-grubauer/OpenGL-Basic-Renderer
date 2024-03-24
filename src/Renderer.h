//
// Created by gruba on 3/23/2024.
//
#ifndef RENDERER_H
#define RENDERER_H
#define ASSERT(x) if(!(x)) __debugbreak()
#define GlCall(x) GLClearError();\
    x;\
    ASSERT(GlLogCall(#x, __FILE__, __LINE__))
#include "BufferObjects/IndexBuffer.h"
#include "BufferObjects/VertexArray.h"
#include "Shader.h"

void GLClearError();
bool GlLogCall(const char* function, const char* file, int line);

class Renderer {
public:
    void drawQuad()const;
    void drawTriangle()const;
    void clear() const;
    void drawTest(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};

#endif //RENDERER_H
