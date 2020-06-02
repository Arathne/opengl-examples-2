add_executable( uniform-2 main.cpp ${OTHER_CPP} )

set( vertexShader "${CMAKE_CURRENT_SOURCE_DIR}/shader.vertex" )
set( fragmentShader "${CMAKE_CURRENT_SOURCE_DIR}/shader.fragment" )

target_compile_definitions( uniform-2 PRIVATE VERTEX_SHADER_PATH="${vertexShader}" )
target_compile_definitions( uniform-2 PRIVATE FRAGMENT_SHADER_PATH="${fragmentShader}" )

target_link_libraries( uniform-2 glfw OpenGL::GL )
