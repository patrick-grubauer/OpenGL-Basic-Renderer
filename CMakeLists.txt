cmake_minimum_required(VERSION 3.27)
project(OpenGLIntro)
include(FetchContent)
set(CMAKE_CXX_STANDARD 20)

add_executable(openglintro 
        src/main.cpp
        src/Renderer.cpp
        src/Renderer.h
        src/BufferObjects/VertexBuffer.cpp
        src/BufferObjects/VertexBuffer.h
        src/BufferObjects/IndexBuffer.cpp
        src/BufferObjects/IndexBuffer.h
        src/BufferObjects/VertexArray.cpp
        src/BufferObjects/VertexBufferLayout.cpp
        src/BufferObjects/VertexBufferLayout.h
        src/Shader.cpp
        src/Shader.h
        src/BufferObjects/VertexArray.h
        src/BufferObjects/Texture.cpp
        src/BufferObjects/Texture.h
        "${CMAKE_SOURCE_DIR}/extern/glad/glad.h" "${CMAKE_SOURCE_DIR}/extern/glad/glad.c"
        "${CMAKE_SOURCE_DIR}/extern/stb_image.h" "${CMAKE_SOURCE_DIR}/extern/stb_image.cpp"
)

FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git)
FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm.git)
FetchContent_MakeAvailable(glfw glm)
target_link_libraries(openglintro glfw glm::glm)


 
target_include_directories(openglintro PUBLIC "${CMAKE_SOURCE_DIR}/extern")
file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_INSTALL_PREFIX})

# compile commands
if(EXISTS "${CMAKE_INSTALL_PREFIX}/compile_commands.json")
    file(CREATE_LINK "${CMAKE_INSTALL_PREFIX}/compile_commands.json" "${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json")
endif()



