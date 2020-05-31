add_executable( color main.cpp ${OTHER_CPP} )

set( vertexShader "${CMAKE_CURRENT_SOURCE_DIR}/shader.vertex" )
set( fragmentShader "${CMAKE_CURRENT_SOURCE_DIR}/shader.fragment" )

target_compile_definitions( color PRIVATE VERTEX_SHADER_PATH="${vertexShader}" )
target_compile_definitions( color PRIVATE FRAGMENT_SHADER_PATH="${fragmentShader}" )

target_link_libraries( color glfw OpenGL::GL )
