//
// Created by gruba on 3/23/2024.
//

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

class VertexBuffer {
private:
    unsigned int m_RendererId;

public:
    VertexBuffer(const void* data, unsigned int size);

    ~VertexBuffer();

    void bind() const;

    void unbind() const;
};

#endif //VERTEXBUFFER_H
