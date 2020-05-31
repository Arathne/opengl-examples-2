cmake_minimum_required( VERSION 3.16.2 )

project( basic 
        VERSION 1.0
        DESCRIPTION "OpenGL Examples"
        LANGUAGES CXX C )

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build )

find_package( OpenGL REQUIRED )

include_directories( include )
add_subdirectory( other )

add_subdirectory( window )
add_subdirectory( shader )
add_subdirectory( square-1 )
add_subdirectory( square-2 )
add_subdirectory( square-3 )
