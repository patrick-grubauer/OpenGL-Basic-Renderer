//
// Created by gruba on 3/23/2024.
//
#ifndef RENDERER_H
#define RENDERER_H
#define ASSERT(x) if(!(x)) __debugbreak()
#define GlCall(x) GLClearError();\
    x;\
    ASSERT(GlLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GlLogCall(const char* function, const char* file, int line);


#endif //RENDERER_H
