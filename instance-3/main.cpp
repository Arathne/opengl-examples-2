#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader/ShaderProgram.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void resize_callback( GLFWwindow* window, int width, int height );
void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods );

int main()
{
    std::cout << "grid structure with instancing" << std::endl;

    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    GLFWwindow* window = glfwCreateWindow( 600, 600, "instance-3", nullptr, nullptr );
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
    
    glm::vec2 offsets[] = {
        glm::vec2(1, 1),
        glm::vec2(5, 5),
        glm::vec2(2, 4),
        glm::vec2(4, 2)
    };
       
    float vertices[] = {
        -1.0f, -1.0f,
        -1.0f,  0.0f,
         0.0f,  0.0f,
         0.0f, -1.0f
    };
    
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    unsigned int VAO, VBO, EBO, instanceVBO;
    
    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );
    glGenBuffers( 1, &EBO );
    glGenBuffers( 1, &instanceVBO );

    glBindVertexArray( VAO );

    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*) 0 );
    glEnableVertexAttribArray( 0 );

    glBindBuffer( GL_ARRAY_BUFFER, instanceVBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(offsets), &offsets[0], GL_STATIC_DRAW );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*) 0 );
    glEnableVertexAttribArray( 1 );
    glVertexAttribDivisor( 1, 1 );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW );

    glm::mat4 orthographic = glm::ortho( 0.0f, 5.0f, 0.0f, 5.0f, -1.0f, 1.0f );
    shaderProgram.setUniformMat4fv( "ortho", orthographic );
    
    glm::mat4 model = glm::mat4(1.0f);
    shaderProgram.setUniformMat4fv( "model", model );

    while( !glfwWindowShouldClose(window) )
    {
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );
        
        glBindVertexArray( VAO );
        glDrawElementsInstanced( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 5);

        glfwSwapBuffers( window );
        glfwPollEvents();
    }
    
    glDeleteVertexArrays( 1, &VAO );
    glDeleteBuffers( 1, &VBO );
    glDeleteBuffers( 1, &EBO );
    glDeleteBuffers( 1, &instanceVBO );
    glfwTerminate();

    return 0;
}

void resize_callback( GLFWwindow* window, int width, int height )
{
    glViewport( 0, 0, 600, 600 );
}

void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
    if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
    {
        glfwSetWindowShouldClose( window, true );
    }
}
