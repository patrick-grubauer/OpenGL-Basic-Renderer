//
// Created by gruba on 3/23/2024.
//

#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H
#include "VertexBuffer.h"
#include "VertexArray.h"

class VertexBufferLayout;
class VertexArray {
private:
    unsigned int m_RenderId;
public:
    VertexArray();

    ~VertexArray();

    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void bind() const;
    void unbind() const;

};


#endif //VERTEXARRAY_H
