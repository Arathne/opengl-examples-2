add_executable( shader main.cpp ${OTHER_CPP} )

target_link_libraries( shader glfw OpenGL::GL )
