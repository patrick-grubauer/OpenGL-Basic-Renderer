#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include  <fstream>
#include  <string>
#include  <sstream>
#define ASSERT(x) if(!(x)) __debugbreak()
#define GlCall(x) GLClearError();\
    x;\
    ASSERT(GlLogCall(#x, __FILE__, __LINE__))

static void GLClearError() {
    while (glGetError());
}

static bool GlLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << ") Function:"<<function<<" File:"<<file<<":"<<line << std::endl;
        return false;
    }
    return true;
}


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
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);

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


    //id
    GLuint VBO;
    //Generate 1 buffer with this id
    glGenBuffers(1, &VBO);
    //Say that the buffer with id VBO is Array_Buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Coping Data into this buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //specifying layout
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2,GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, (GLvoid *) 0);
    GLuint IBO;
    //Generate 1 buffer with this id
    glGenBuffers(1, &IBO);
    //Say that the buffer with id VBO is Array_Buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    //Coping Data into this buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    ShaderProgramSource source = ParseShader("res\\shaders\\Basic.shader");
    unsigned int program = createShader(source.VertexSource, source.FragmentSource);
    glUseProgram(program);
    while (!glfwWindowShouldClose(window)) {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
        // Render

        // Draw our first triangle
        GlCall(glDrawElements(GL_TRIANGLES, 6, GL_INT, nullptr););
        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}
