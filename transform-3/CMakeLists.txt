add_executable( transform-3 main.cpp ${OTHER_CPP} ${TEXTURE_CPP} )

set( vertex "${CMAKE_CURRENT_SOURCE_DIR}/shader.vertex" )
set( fragment "${CMAKE_CURRENT_SOURCE_DIR}/shader.fragment" )
set( face "${TEXTURE_DIR}/face.png" )
set( container "${TEXTURE_DIR}/container.jpg" )

target_compile_definitions( transform-3 PRIVATE VERTEX_SHADER_PATH="${vertex}" )
target_compile_definitions( transform-3 PRIVATE FRAGMENT_SHADER_PATH="${fragment}" )
target_compile_definitions( transform-3 PRIVATE FACE_PNG="${face}" )
target_compile_definitions( transform-3 PRIVATE CONTAINER_JPG="${container}" )

target_link_libraries( transform-3 glfw OpenGL::GL )
