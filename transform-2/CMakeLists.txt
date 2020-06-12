add_executable( transform-2 main.cpp ${OTHER_CPP} ${TEXTURE_CPP} )

set( vertex "${CMAKE_CURRENT_SOURCE_DIR}/shader.vertex" )
set( fragment "${CMAKE_CURRENT_SOURCE_DIR}/shader.fragment" )
set( fragment2 "${CMAKE_CURRENT_SOURCE_DIR}/shader.fragment2" )

target_compile_definitions( transform-2 PRIVATE VERTEX_SHADER_PATH="${vertex}" )
target_compile_definitions( transform-2 PRIVATE FRAGMENT_SHADER_PATH="${fragment}" )
target_compile_definitions( transform-2 PRIVATE FRAGMENT2_SHADER_PATH="${fragment2}" )

target_link_libraries( transform-2 glfw OpenGL::GL )
