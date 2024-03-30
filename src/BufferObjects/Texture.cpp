//
// Created by gruba on 3/24/2024.
//

#include "Texture.h"

#include <glad/glad.h>

#include "../Renderer.h"
#include "../res/vendor/stb_image.h"

Texture::Texture(const std::string &path) : m_FilePath(path), m_LocalPuffer(nullptr)
{
    stbi_set_flip_vertically_on_load(1);
    m_LocalPuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    GlCall(glGenTextures(1, &m_RendererId));
    GlCall(glBindTexture(GL_TEXTURE_2D, m_RendererId));

    GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalPuffer));
    GlCall(glBindTexture(GL_TEXTURE_2D, 0));

    if (m_LocalPuffer)
        stbi_image_free(m_LocalPuffer);
}

Texture::~Texture()
{
    GlCall(glDeleteTextures(1, &m_RendererId));
}

void Texture::bind(unsigned int slot) const
{
    GlCall(glActiveTexture(GL_TEXTURE0 + slot));
    GlCall(glBindTexture(GL_TEXTURE_2D, m_RendererId));
}

void Texture::unbind() const
{
    GlCall(glBindTexture(GL_TEXTURE_2D, 0));
}
