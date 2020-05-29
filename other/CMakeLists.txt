set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )

set( GLFW_BUILD_TEXTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )

add_subdirectory( glfw )

set( 
    OTHER_CPP 
        "${CMAKE_CURRENT_SOURCE_DIR}/glad.c" 
        "${CMAKE_CURRENT_SOURCE_DIR}/ShaderProgram.cpp" 
        "${CMAKE_CURRENT_SOURCE_DIR}/Shader.cpp" 
        PARENT_SCOPE
)
