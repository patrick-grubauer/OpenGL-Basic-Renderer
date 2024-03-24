//
// Created by gruba on 3/24/2024.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>


class Texture {
private:
    unsigned int m_RendererId;
    std::string m_FilePath;
    unsigned char* m_LocalPuffer;
    int m_Width, m_Height, m_BPP;

public:
    Texture(const std::string& path);

    ~Texture();

    void bind(unsigned int slot = 0) const;

    void unbind() const;

    int getWidth() const {
        return m_Width;
    }

    int getHeight() const {
        return m_Height;
    }
};


#endif //TEXTURE_H
