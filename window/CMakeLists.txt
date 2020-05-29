add_executable( window main.cpp ${OTHER_CPP} )

target_link_libraries( window glfw OpenGL::GL )
