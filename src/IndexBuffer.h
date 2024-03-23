//
// Created by gruba on 3/23/2024.
//

#ifndef IndexBuffer_H
#define IndexBuffer_H

class IndexBuffer {
private:
    unsigned int m_RendererId;
    unsigned int m_Count;

public:
    IndexBuffer(const void* data, unsigned int count);

    ~IndexBuffer();

    void bind() const;

    void unbind() const;

    unsigned int getCount() const { return m_Count; }
};

#endif //IndexBuffer_H


//
