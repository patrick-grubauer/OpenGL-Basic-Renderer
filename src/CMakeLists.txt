cmake_minimum_required(VERSION 3.27)
project(OpenGLIntro)

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
)
include_directories("C:/cpplibs/GLEW/include")
target_link_libraries(openglintro "C:/cpplibs/GLEW/glew32sd.lib")

include_directories("C:/cpplibs/GLFW/include")
target_link_libraries(openglintro "C:/cpplibs/GLFW/glfw3.lib")
target_link_libraries(openglintro "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64/OpenGL32.Lib")


