add_executable( shader main.cpp ${OTHER_CPP} )

set( vertexShader "${CMAKE_CURRENT_SOURCE_DIR}/vertex.shader" ) 
set( fragmentShader "${CMAKE_CURRENT_SOURCE_DIR}/fragment.shader" ) 

target_compile_definitions( shader PRIVATE VERTEX_SHADER_PATH="${vertexShader}" )
target_compile_definitions( shader PRIVATE FRAGMENT_SHADER_PATH="${fragmentShader}" )

target_link_libraries( shader glfw OpenGL::GL )
