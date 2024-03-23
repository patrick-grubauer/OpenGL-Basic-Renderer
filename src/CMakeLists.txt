cmake_minimum_required(VERSION 3.27)
project(OpenGLIntro)

set(CMAKE_CXX_STANDARD 20)
add_executable(openglintro main.cpp
        Renderer.cpp
        Renderer.h
        VertexBuffer.cpp
        VertexBuffer.h
        IndexBuffer.cpp
        IndexBuffer.h
        VertexArray.cpp
        VertexArray.h
        VertexBufferLayout.cpp
        VertexBufferLayout.h
)
include_directories("C:/cpplibs/GLEW/include")
target_link_libraries(openglintro "C:/cpplibs/GLEW/glew32sd.lib")

include_directories("C:/cpplibs/GLFW/include")
target_link_libraries(openglintro "C:/cpplibs/GLFW/glfw3.lib")
target_link_libraries(openglintro "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64/OpenGL32.Lib")


