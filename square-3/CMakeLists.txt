add_executable( square-3 main.cpp ${OTHER_CPP} )

set( vertexShader "${CMAKE_CURRENT_SOURCE_DIR}/shader.vertex" )
set( fragmentShader "${CMAKE_CURRENT_SOURCE_DIR}/shader.fragment" )

target_compile_definitions( square-3 PRIVATE VERTEX_SHADER_PATH="${vertexShader}" )
target_compile_definitions( square-3 PRIVATE FRAGMENT_SHADER_PATH="${fragmentShader}" )

target_link_libraries( square-3 glfw OpenGL::GL )
