add_executable( camera-2 main.cpp ${OTHER_CPP} ${TEXTURE_CPP} )

set( vertex "${CMAKE_CURRENT_SOURCE_DIR}/shader.vertex" )
set( fragment "${CMAKE_CURRENT_SOURCE_DIR}/shader.fragment" )
set( container "${TEXTURE_DIR}/container.jpg" )
set( face "${TEXTURE_DIR}/face.png" )

target_compile_definitions( camera-2 PRIVATE VERTEX_SHADER="${vertex}" )
target_compile_definitions( camera-2 PRIVATE FRAGMENT_SHADER="${fragment}" )
target_compile_definitions( camera-2 PRIVATE CONTAINER_JPG="${container}" )
target_compile_definitions( camera-2 PRIVATE FACE_PNG="${face}" )

target_link_libraries( camera-2 glfw OpenGL::GL )
