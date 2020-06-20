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
add_subdirectory( wireframe )
add_subdirectory( color )

add_subdirectory( texture-1 )
add_subdirectory( texture-2 )
add_subdirectory( texture-3 )
add_subdirectory( texture-4 )
add_subdirectory( texture-5 )
add_subdirectory( texture-6 )

add_subdirectory( shader-1 )
add_subdirectory( shader-2 )
add_subdirectory( shader-3 )
add_subdirectory( shader-4 )

add_subdirectory( uniform-1 )
add_subdirectory( uniform-2 )

add_subdirectory( square-1 )
add_subdirectory( square-2 )
add_subdirectory( square-3 )

add_subdirectory( transform-1 )
add_subdirectory( transform-2 )
add_subdirectory( transform-3 )
add_subdirectory( transform-4 )

add_subdirectory( camera-1 )
add_subdirectory( camera-2 )
add_subdirectory( camera-3 )
add_subdirectory( camera-4 )

add_subdirectory( instance-1 )
add_subdirectory( instance-2 )
