add_executable( transform-4 main.cpp ${OTHER_CPP} ${TEXTURE_CPP} )

set( vertex "${CMAKE_CURRENT_SOURCE_DIR}/shader.vertex" )
set( fragment "${CMAKE_CURRENT_SOURCE_DIR}/shader.fragment" )
set( container "${TEXTURE_DIR}/container.jpg" )
set( face "${TEXTURE_DIR}/face.png" )

target_compile_definitions( transform-4 PRIVATE VERTEX_SHADER_PATH="${vertex}" )
target_compile_definitions( transform-4 PRIVATE FRAGMENT_SHADER_PATH="${fragment}" )
target_compile_definitions( transform-4 PRIVATE CONTAINER_JPG="${container}" )
target_compile_definitions( transform-4 PRIVATE FACE_PNG="${face}" )

target_link_libraries( transform-4 glfw OpenGL::GL )
