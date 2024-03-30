cmake_minimum_required(VERSION 3.27)
project(OpenGLIntro)
include(FetchContent)
set(CMAKE_CXX_STANDARD 20)

add_executable(openglintro main.cpp
        Renderer.cpp
        Renderer.h
        BufferObjects/VertexBuffer.cpp
        BufferObjects/VertexBuffer.h
        BufferObjects/IndexBuffer.cpp
        BufferObjects/IndexBuffer.h
        BufferObjects/VertexArray.cpp
        BufferObjects/VertexBufferLayout.cpp
        BufferObjects/VertexBufferLayout.h
        Shader.cpp
        Shader.h
        BufferObjects/VertexArray.h
        res/vendor/stb_image.cpp
        res/vendor/stb_image.h
        BufferObjects/Texture.cpp
        BufferObjects/Texture.h
        "${CMAKE_SOURCE_DIR}/extern/glad/glad.h" "${CMAKE_SOURCE_DIR}/extern/glad/glad.c"

)

FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git)
FetchContent_MakeAvailable(glfw)
target_link_libraries(openglintro glfw)
target_include_directories(openglintro PUBLIC "${CMAKE_SOURCE_DIR}/extern")
MESSAGE (${CMAKE_SOURCE_DIR}/res)
file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_INSTALL_PREFIX})

# compile commands
if(EXISTS "${CMAKE_INSTALL_PREFIX}/compile_commands.json")
    file(CREATE_LINK "${CMAKE_INSTALL_PREFIX}/compile_commands.json" "${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json")
endif()



