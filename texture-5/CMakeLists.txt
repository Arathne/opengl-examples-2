add_executable( texture-5 main.cpp ${OTHER_CPP} )

set( vertexShader "${CMAKE_CURRENT_SOURCE_DIR}/shader.vertex" )
set( fragmentShader "${CMAKE_CURRENT_SOURCE_DIR}/shader.fragment" )
set( container "${TEXTURE_DIR}/container.jpg" )
set( face "${TEXTURE_DIR}/face.png" )

target_compile_definitions( texture-5 PRIVATE VERTEX_SHADER_PATH="${vertexShader}" )
target_compile_definitions( texture-5 PRIVATE FRAGMENT_SHADER_PATH="${fragmentShader}" )
target_compile_definitions( texture-5 PRIVATE CONTAINER_JPG="${container}" )
target_compile_definitions( texture-5 PRIVATE FACE_PNG="${face}" )

target_link_libraries( texture-5 glfw OpenGL::GL )
