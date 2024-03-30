#include <glad/glad.h>
#include <iostream>

// GLFW
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>

#include "BufferObjects/IndexBuffer.h"
#include "BufferObjects/Texture.h"
#include "BufferObjects/VertexArray.h"
#include "BufferObjects/VertexBuffer.h"
#include "BufferObjects/VertexBufferLayout.h"
#include "Renderer.h"
#include "Shader.h"

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mode) {
  // When a user presses the escape key, we set the WindowShouldClose property
  // to true closing the application
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

// The MAIN function, from here we start the application and run the game loop
int main() {
  // Init GLFW
  glfwInit();
  // Create a GLFWwindow object that we can use for GLFW's functions
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress))) {
    glfwDestroyWindow(window);
    glfwTerminate();
  }

  // Set the required callback functions
  glfwSetKeyCallback(window, key_callback);
  glfwSwapInterval(6);

  // Define the viewport dimensions
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  glfwSetKeyCallback(window, key_callback);
  // Game loop
  GLfloat vertices[] = {-0.5, -0.5, 0.0f, 0.0f, 0.5,  -0.5, 1.0f, 0.0f,
                        0.5,  0.5,  1.0f, 1.0f, -0.5, 0.5,  0.0f, 1.0f};
  unsigned int indices[] = {0, 1, 2, 2, 3, 0};
  {
    VertexArray va;
    VertexBuffer vb(vertices, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(2);

    va.addBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.5f, 1.5f, -1.0f, 1.0f);

    Shader shader("res\\shaders\\Basic.shader");
    shader.bind();
    shader.setUniformMat4f("u_MVP", proj);
    Renderer renderer;

    Texture texture("res\\textures\\queen.jpg");
    texture.bind();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    float r = 0.0f;
    float increment = 0.05f;
    while (!glfwWindowShouldClose(window)) {
      glfwPollEvents();
      renderer.clear();
      // Alpha-Blending aktivieren

      shader.setUniform1i("u_Texture", 0);

      renderer.drawTest(va, ib, shader);

      if (r > 1.0f)
        increment = -0.05f;
      else if (r < 0.0f)
        increment = 0.05f;
      r += increment;
      glfwSwapBuffers(window);
    }
  }
  glfwTerminate();
  return 0;
}
