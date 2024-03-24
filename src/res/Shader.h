//
// Created by gruba on 3/24/2024.
//

#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <unordered_map>

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader {
private:
    unsigned int m_RendererId;
    const std::string m_Filepath;
    std::unordered_map<std::string, unsigned int> uniform_locations;

public:
    Shader(const std::string& path);

    ~Shader();

    void bind() const;

    void unbind() const;

    void setUniform4f(const std::string& name, float v1, float v2, float v3, float v4);

private:
    unsigned int getUnifromLocation(const std::string& name);

    unsigned int createShader(const std::string& vetexShader, const std::string& fragmentShader);

    unsigned int compileShader(unsigned int type, const std::string& source);

    ShaderProgramSource parseShader();
};


#endif //SHADER_H
