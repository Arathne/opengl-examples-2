add_executable( ortho main.cpp ${OTHER_CPP} )

set( vertex "${CMAKE_CURRENT_SOURCE_DIR}/shader.vertex" )
set( fragment "${CMAKE_CURRENT_SOURCE_DIR}/shader.fragment" )

target_compile_definitions( ortho PRIVATE VERTEX_SHADER="${vertex}" )
target_compile_definitions( ortho PRIVATE FRAGMENT_SHADER="${fragment}" )

target_link_libraries( ortho glfw OpenGL::GL )
