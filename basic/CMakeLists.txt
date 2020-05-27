add_executable( basic main.cpp ${GLAD_CPP} )

target_link_libraries( basic glfw OpenGL::GL )
