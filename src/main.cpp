#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include  <fstream>
#include  <string>
#include  <sstream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;


static ShaderProgramSource ParseShader(const std::string& location) {
    std::ifstream stream(location);
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

void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mode) {
    // When a user presses the escape key, we set the WindowShouldClose property to true
    // closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

static unsigned int compileShader(unsigned int type, const std::string& source) {
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

static unsigned int createShader(const std::string& vetexShader, const std::string& fragmentShader) {
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

// The MAIN function, from here we start the application and run the game loop
int main() {
    // Init GLFW
    glfwInit();
    // Create a GLFWwindow object that we can use for GLFW's functions
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSwapInterval(6);
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glfwSetKeyCallback(window, key_callback);
    // Game loop
    GLfloat vertices[] = {
        -0.5, -0.5,
        0.5, -0.5,
        0.5, 0.5,
        -0.5, 0.5,
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };


    GLuint VAO;
    GlCall(glGenVertexArrays(1,&VAO));
    GlCall(glBindVertexArray(VAO));
    //id
    VertexBuffer vb(vertices, 4 * 2 * sizeof(GLuint));
    GlCall(glEnableVertexAttribArray(0));
    GlCall(glVertexAttribPointer(0, 2,GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, (GLvoid *) 0));

    IndexBuffer ib(indices, 6);

    ShaderProgramSource source = ParseShader("res\\shaders\\Basic.shader");
    unsigned int program = createShader(source.VertexSource, source.FragmentSource);


    int location = glGetUniformLocation(program, "u_Color");
    ASSERT(location>-1);
    GlCall(glBindVertexArray(0));
    GlCall(glUseProgram(0));
    float r = 0.0f;
    float increment = 0.05f;
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        GlCall(glClear(GL_COLOR_BUFFER_BIT));

        GlCall(glUseProgram(program));
        GlCall(glUniform4f(location, 0.8f, r, 1, 1.0f));

        GlCall(glBindVertexArray(VAO));
        // ib.bind();
        GlCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr););
        if (r > 1.0f)
            increment = -0.05f;
        else if (r < 0.0f)
            increment = 0.05f;
        r += increment;
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
