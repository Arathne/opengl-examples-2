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
    std::cout << "4 vertices to draw two squares in different positions" << std::endl;
 
    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    GLFWwindow* window = glfwCreateWindow( 600, 600, "transform-2", nullptr, nullptr );
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

    ShaderProgram shaderProgram1( VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH );
    shaderProgram1.link();
    
    ShaderProgram shaderProgram2( VERTEX_SHADER_PATH, FRAGMENT2_SHADER_PATH );
    shaderProgram2.link();
    
    float vertices[] = {
        0.5f,  0.5f,
        0.5f, -0.5f,
       -0.5f, -0.5f,
       -0.5f,  0.5f
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int VBO, EBO, VAO;
    
    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );
    glGenBuffers( 1, &EBO );
    
    glBindVertexArray( VAO );
    
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
    
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW );
    
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*) 0 );
    glEnableVertexAttribArray( 0 );
    
    while( !glfwWindowShouldClose(window) )
    {
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );


        shaderProgram1.use();
        glm::mat4 transform = glm::mat4( 1.0f );
        transform = glm::scale( transform, glm::vec3(0.5f, 0.5f, 0.5f) );
        transform = glm::translate( transform, glm::vec3(0.5f, 0.5f, 0.0f) );
        
        shaderProgram1.getUniform( "transform" );
        shaderProgram1.setUniformMat4fv( transform );

        glBindVertexArray( VAO );
        glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
        
        
        shaderProgram2.use();
        transform = glm::mat4( 1.0f );
        transform = glm::scale( transform, glm::vec3(0.5f, 0.5f, 0.5f) );
        transform = glm::translate( transform, glm::vec3(-0.5f, -0.5f, 0.0f) );
        
        shaderProgram2.getUniform( "transform" );
        shaderProgram2.setUniformMat4fv( transform );

        glBindVertexArray( VAO );
        glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );


        glfwSwapBuffers( window );
        glfwPollEvents();
    }
    
    glDeleteVertexArrays( 1, &VAO );
    glDeleteBuffers( 1, &VBO );
    glDeleteBuffers( 1, &EBO );
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
        glfwSetWindowShouldClose( window, true );
    }
}
