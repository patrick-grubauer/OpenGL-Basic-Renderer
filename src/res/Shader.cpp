//
// Created by gruba on 3/24/2024.
//

#include "Shader.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <GL/glew.h>

#include "../Renderer.h"


ShaderProgramSource Shader::parseShader() {
    std::ifstream stream(m_Filepath);
    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        } else {
            std::string asd;
            ss[(int) type] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}


unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = &source[0];
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id,GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH, &length);
        char message[length];
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile" << ((type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment") << " shader" <<
                std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int Shader::createShader(const std::string& vetexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vetexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    //Link the shaders to program.
    glLinkProgram(program);
    glValidateProgram(program);
    //delete shaders in memory as executalbe already got created
    glDeleteShader(vs);
    glDeleteShader(fs);
    int validationStatus = GL_FALSE;
    glGetProgramiv(program,GL_VALIDATE_STATUS, &validationStatus);
    if (validationStatus == GL_FALSE) {
        exit(64);
    }
    return program;
}

Shader::Shader(const std::string& path): m_Filepath(path) {
    auto shaders = parseShader();
    m_RendererId = createShader(shaders.VertexSource, shaders.FragmentSource);
}

Shader::~Shader() {
    GlCall(glDeleteProgram(m_RendererId));
}

void Shader::bind() const{
    GlCall(glUseProgram(m_RendererId));
}

void Shader::unbind() const{
    GlCall(glUseProgram(0));
}

void Shader::setUniform4f(const std::string& name, float v1, float v2, float v3, float v4) {
    if (uniform_locations.find(name) != uniform_locations.end()) {
        GlCall(glUniform4f(uniform_locations[name], v1,v2,v3,v4));
    } else {
        GlCall(glUniform4f( getUnifromLocation(name), v1, v2, v3, v4));
    }
}

unsigned int Shader::getUnifromLocation(const std::string& name) {
    GlCall(int location = glGetUniformLocation(m_RendererId, &name[0]));
    if (location < 0)
        std::cout << "Uniform not found!" << std::endl;
    uniform_locations[name] = location;
    return location;
}
