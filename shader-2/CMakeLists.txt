add_executable( shader-2 main.cpp ${OTHER_CPP} )

set( vertexShader "${CMAKE_CURRENT_SOURCE_DIR}/shader.vertex" )
set( fragmentShader "${CMAKE_CURRENT_SOURCE_DIR}/shader.fragment" )
set( fragmentShader2 "${CMAKE_CURRENT_SOURCE_DIR}/shader.fragment2" )

target_compile_definitions( shader-2 PRIVATE VERTEX_SHADER_PATH="${vertexShader}" )
target_compile_definitions( shader-2 PRIVATE FRAGMENT_SHADER_PATH="${fragmentShader}" )
target_compile_definitions( shader-2 PRIVATE FRAGMENT2_SHADER_PATH="${fragmentShader2}" )

target_link_libraries( shader-2 glfw OpenGL::GL )
