cmake_minimum_required(VERSION 3.27)
project(basic_renderer)
include(FetchContent)
set(CMAKE_CXX_STANDARD 20)

FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git)
FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm.git)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG master
)


FetchContent_MakeAvailable(glfw glm imgui)
file(GLOB IMGUI_SRC
    ${imgui_SOURCE_DIR}/*.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    src/Renderer.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    src/BufferObjects/VertexBuffer.cpp
)


add_executable(basic_renderer 
        src/main.cpp
        src/Renderer.h
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
        "${IMGUI_SRC}"
        )
target_include_directories(basic_renderer
        PUBLIC
            ${imgui_SOURCE_DIR}
            ${imgui_SOURCE_DIR}/backends
            ${imgui_SOURCE_DIR}/examples
)

target_link_libraries(basic_renderer glfw glm::glm)


 
target_include_directories(basic_renderer PUBLIC "${CMAKE_SOURCE_DIR}/extern")
file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_INSTALL_PREFIX})

# compile commands
if(EXISTS "${CMAKE_INSTALL_PREFIX}/compile_commands.json")
    file(CREATE_LINK "${CMAKE_INSTALL_PREFIX}/compile_commands.json" "${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json")
endif()



