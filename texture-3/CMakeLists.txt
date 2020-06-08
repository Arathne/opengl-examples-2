add_executable( texture-3 main.cpp ${OTHER_CPP} )

set( vertexShader "${CMAKE_CURRENT_SOURCE_DIR}/shader.vertex" )
set( fragmentShader "${CMAKE_CURRENT_SOURCE_DIR}/shader.fragment" )
set( facepng "${TEXTURE_DIR}/face.png" )

target_compile_definitions( texture-3 PRIVATE VERTEX_SHADER_PATH="${vertexShader}" )
target_compile_definitions( texture-3 PRIVATE FRAGMENT_SHADER_PATH="${fragmentShader}" )
target_compile_definitions( texture-3 PRIVATE FACE_PNG="${facepng}" )

target_link_libraries( texture-3 glfw OpenGL::GL )
