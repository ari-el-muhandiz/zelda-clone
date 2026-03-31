# engine/CMakeLists.txt

add_library(engine 
    input/InputManager.cpp
    graphics/Mesh.cpp
    graphics/Shader.cpp
    graphics/Material.cpp
    graphics/Renderer.cpp
    graphics/opengl/OpenGLContext.cpp
    graphics/opengl/OpenGLGraphicsEngine.cpp
    graphics/opengl/OpenGLRenderer.cpp
)

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(engine
    PRIVATE
    glad::glad
    ${SDL2_LIBRARIES}
)
