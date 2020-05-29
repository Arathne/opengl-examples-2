add_executable( window main.cpp ${GLAD_CPP} )

target_link_libraries( window glfw OpenGL::GL )
