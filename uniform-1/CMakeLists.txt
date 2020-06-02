add_executable( uniform-1 main.cpp ${OTHER_CPP} )

set( vertexShader "${CMAKE_CURRENT_SOURCE_DIR}/shader.vertex" )
set( fragmentShader "${CMAKE_CURRENT_SOURCE_DIR}/shader.fragment" )

target_compile_definitions( uniform-1 PRIVATE VERTEX_SHADER_PATH="${vertexShader}" )
target_compile_definitions( uniform-1 PRIVATE FRAGMENT_SHADER_PATH="${fragmentShader}" )

target_link_libraries( uniform-1 glfw OpenGL::GL )
