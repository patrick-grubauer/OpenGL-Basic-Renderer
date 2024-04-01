// GLFW
#include "BufferObjects/IndexBuffer.h"
#include "BufferObjects/Texture.h"
#include "BufferObjects/VertexArray.h"
#include "BufferObjects/VertexBuffer.h"
#include "BufferObjects/VertexBufferLayout.h"
#include "Renderer.h"
#include "Shader.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

// Window dimensions
const GLuint WIDTH = 1920, HEIGHT = 1080;

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
  GLfloat vertices[] = {0,    0,       0.0f,    0.0f,    960 / 2, 0,
                        1.0f, 0.0f,    960 / 2, 540 / 2, 1.0f,    1.0f,
                        0,    540 / 2, 0.0f,    1.0f};
  unsigned int indices[] = {0, 1, 2, 2, 3, 0};
  {
    VertexArray va;
    VertexBuffer vb(vertices, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(2);

    va.addBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    glm::mat4 proj = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    Shader shader("res\\shaders\\Basic.shader");
    Renderer renderer;

    // ImGui ////
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    //////

    Texture texture("res\\textures\\queen.jpg");
    texture.bind();

    float r = 0.0f;
    float increment = 0.05f;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glm::vec3 translationA(0, 0, 0);
    glm::vec3 translationB(1920 / 2, 0, 0);

    while (!glfwWindowShouldClose(window)) {
      renderer.clear();

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
      glm::mat4 mvp = proj * view * model;

      shader.bind();
      shader.setUniform1i("u_Texture", 0);
      shader.setUniformMat4f("u_MVP", mvp);
      renderer.drawTest(va, ib, shader);

      model = glm::translate(glm::mat4(1.0f), translationB);
      mvp = proj * view * model;
      shader.setUniformMat4f("u_MVP", mvp);
      renderer.drawTest(va, ib, shader);

      static float f = 0.0f;
      static int counter = 0;

      if (r > 1.0f)
        increment = -0.05f;
      else if (r < 0.0f)
        increment = 0.05f;
      r += increment;

      ImGui::SliderFloat3("TranslationA", &translationA.x, 0.0f, 1920.0 / 2);
      ImGui::SliderFloat3("TranslationB", &translationB.x, 0.0f, 1920.0 / 2);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                  1000.0f / io.Framerate, io.Framerate);
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  }
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwTerminate();
  return 0;
}