add_executable( square-1 main.cpp ${GLAD_CPP} )

target_link_libraries( square-1 glfw OpenGL::GL )
