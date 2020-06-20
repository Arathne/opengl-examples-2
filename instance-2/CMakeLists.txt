add_executable( instance-2 main.cpp ${OTHER_CPP} )

set( vertex "${CMAKE_CURRENT_SOURCE_DIR}/shader.vertex" )
set( fragment "${CMAKE_CURRENT_SOURCE_DIR}/shader.fragment" )

target_compile_definitions( instance-2 PRIVATE VERTEX_SHADER="${vertex}" )
target_compile_definitions( instance-2 PRIVATE FRAGMENT_SHADER="${fragment}" )

target_link_libraries( instance-2 glfw OpenGL::GL )
