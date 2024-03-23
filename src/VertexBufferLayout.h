//
// Created by gruba on 3/23/2024.
//

#ifndef VERTEXBUFFERLAYOUT_H
#define VERTEXBUFFERLAYOUT_H
#include <assert.h>
#include <vector>
#include <GL/glew.h>

#include "Renderer.h"

struct VertexBufferElement {
    unsigned int count;
    unsigned int type;
    unsigned char normalized;

    static unsigned int getSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;

public:
    VertexBufferLayout(): m_Stride(0) {
    }

    template<typename T>
    void push(unsigned int count) {
        static_assert(false);
    }


    template<>
    void push<float>(unsigned int count) {
        m_Elements.push_back({count, GL_FLOAT, GL_FALSE});
        m_Stride += sizeof(GLfloat) * count;
    }

    template<>
    void push<unsigned int>(unsigned int count) {
        m_Elements.push_back({count, GL_UNSIGNED_INT, GL_FALSE});
        m_Stride += sizeof(GLuint) * count;
    }

    template<>
    void push<unsigned char>(unsigned int count) {
        m_Elements.push_back({count, GL_UNSIGNED_BYTE, GL_TRUE});
        m_Stride += sizeof(GLbyte) * count;
    }

    const std::vector<VertexBufferElement>& getElements() const { return m_Elements; }

    unsigned int getStride() const { return m_Stride; }
};


#endif //VERTEXBUFFERLAYOUT_H
