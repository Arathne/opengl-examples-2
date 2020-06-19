#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader/ShaderProgram.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void resize_callback( GLFWwindow* window, int width, int height );
void key_callback( GLFWwindow* window, int key, int scancode, int action, int mod );

int main()
{
    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    GLFWwindow* window = glfwCreateWindow( 600, 600, "instance-1", nullptr, nullptr );
    if( window == nullptr )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent( window );
    if( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport( 0, 0, 600, 600 );
    glfwSetFramebufferSizeCallback( window, resize_callback );
    glfwSetKeyCallback( window, key_callback );

    ShaderProgram shaderProgram( VERTEX_SHADER, FRAGMENT_SHADER );
    shaderProgram.link();
    shaderProgram.use();

    float offsets[] = {
        0.1f,
        0.2f,
        0.3f,
        0.4f
    };

    float vertices[] = {
        -0.05f,  0.05f,
         0.05f, -0.05f,
        -0.05f, -0.05f,
        
        -0.05f,  0.05f,
         0.05f, -0.05f,
         0.05f,  0.05f
    };

    unsigned int VAO, vertexVBO, instanceVBO;

    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &vertexVBO );
    glGenBuffers( 1, &instanceVBO );

    glBindVertexArray( VAO );

    glBindBuffer( GL_ARRAY_BUFFER, vertexVBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*) 0 );
    glEnableVertexAttribArray( 0 );

    glBindBuffer( GL_ARRAY_BUFFER, instanceVBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(offsets), offsets, GL_STATIC_DRAW );
    glVertexAttribPointer( 1, 1, GL_FLOAT, GL_FALSE, 1*sizeof(float), (void*) 0 );
    glEnableVertexAttribArray( 1 );

    glVertexAttribDivisor(1, 1);

    while( !glfwWindowShouldClose(window) )
    {
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );
        
        glBindVertexArray( VAO );
        glDrawArraysInstanced( GL_TRIANGLE_STRIP, 0, 6, 5 );

        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    glDeleteVertexArrays( 1, &VAO );
    glDeleteBuffers( 1, &vertexVBO );
    glDeleteBuffers( 1, &instanceVBO );
    glfwTerminate();

    return 0;
}

void resize_callback( GLFWwindow* window, int width, int height )
{
    glViewport( 0, 0, width, height );
}

void key_callback( GLFWwindow* window, int key, int scancode, int action, int mod )
{
    if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
    {
        glfwSetWindowShouldClose(window, true);
    }
}
