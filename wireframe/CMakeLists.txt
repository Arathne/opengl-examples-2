add_executable( wireframe main.cpp ${OTHER_CPP} )

set( vertexShader "${CMAKE_CURRENT_SOURCE_DIR}/shader.vertex" )
set( fragmentShader "${CMAKE_CURRENT_SOURCE_DIR}/shader.fragment" )

target_compile_definitions( wireframe PRIVATE VERTEX_SHADER_PATH="${vertexShader}" )
target_compile_definitions( wireframe PRIVATE FRAGMENT_SHADER_PATH="${fragmentShader}" )

target_link_libraries( wireframe glfw OpenGL::GL )
