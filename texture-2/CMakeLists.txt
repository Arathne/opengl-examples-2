add_executable( texture-2 main.cpp ${OTHER_CPP} )

set( vertexShader "${CMAKE_CURRENT_SOURCE_DIR}/shader.vertex" )
set( fragmentShader "${CMAKE_CURRENT_SOURCE_DIR}/shader.fragment" )
set( container "${TEXTURE_DIR}/container.jpg" )

target_compile_definitions( texture-2 PRIVATE VERTEX_SHADER_PATH="${vertexShader}" )
target_compile_definitions( texture-2 PRIVATE FRAGMENT_SHADER_PATH="${fragmentShader}" )
target_compile_definitions( texture-2 PRIVATE CONTAINER_JPG="${container}" )

target_link_libraries( texture-2 glfw OpenGL::GL )
