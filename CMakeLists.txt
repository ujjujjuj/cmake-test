cmake_minimum_required(VERSION 3.24.3)

project(glBasic)

# option(DEBUG_MODE "Debug Mode" OFF)
# if(DEBUG_MODE)
#     set(ENV{DEBUG_MODE} "1")
# endif()

set(SOURCES
    main.cpp
    Renderer.cpp
    VertexBuffer.cpp
    IndexBuffer.cpp
    VertexBufferLayout.cpp
    VertexArray.cpp
    Shader.cpp
)

set(HEADERS
    Renderer.h
    VertexBuffer.h
    IndexBuffer.h
    VertexBufferLayout.h
    VertexArray.h
    Shader.h
)

list(TRANSFORM HEADERS PREPEND "include/")
list(TRANSFORM SOURCES PREPEND "src/")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} lib/glfw/include lib/glew-cmake/include include/)
add_subdirectory(lib/glfw lib/glew-cmake)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARY} glfw GLEW)
