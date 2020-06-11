#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader/ShaderProgram.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void resize_callback( GLFWwindow* window, int width, int height );
void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods );

int main()
{   
    std::cout << "reflects texture coordinates over y-axis" << std::endl;

    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    GLFWwindow* window = glfwCreateWindow( 600, 600, "texture-3", nullptr, nullptr );
    if( window == nullptr )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent( window );
    if( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) )
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback( window, resize_callback );
    glfwSetKeyCallback( window, key_callback );

    ShaderProgram shaderProgram( VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH );
    shaderProgram.link();
    shaderProgram.use();

    float vertices[] = {
        // vertices       // texture coords
        0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
       -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    
    unsigned int VBO, VAO, EBO;

    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );
    glGenBuffers( 1, &EBO );

    glBindVertexArray( VAO );

    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*) 0 );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*) (3*sizeof(float)) );

    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    
    unsigned int texture1;
    glGenTextures( 1, &texture1 );
    glBindTexture( GL_TEXTURE_2D, texture1 );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    stbi_set_flip_vertically_on_load( true );

    int width, height, channels;
    unsigned char* data = stbi_load( FACE_PNG, &width, &height, &channels, 0 );

    if( data )
    {
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
        glGenerateMipmap( GL_TEXTURE_2D );
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        std::cout << FACE_PNG << std::endl;
    }

    stbi_image_free( data );

    shaderProgram.getUniform( "texture1" );
    shaderProgram.setUniform1i( 0 );
    
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, texture1 );

    while( !glfwWindowShouldClose(window) )
    {
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );
        
        glBindVertexArray( VAO );
        glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    glDeleteVertexArrays( 1, &VAO );
    glDeleteBuffers( 1, &VBO );
    glDeleteBuffers( 1, &EBO );
    glDeleteTextures( 1, &texture1 );
    glfwTerminate();

    return 0;
}

void resize_callback( GLFWwindow* window, int width, int height )
{
    glViewport( 0, 0, width, height );
}

void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
    if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
    {
        glfwSetWindowShouldClose( window, true );
    }
}
