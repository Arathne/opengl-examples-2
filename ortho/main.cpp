#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader/ShaderProgram.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void resize_callback( GLFWwindow* window, int width, int height );
void key_callback( GLFWwindow* window, int key, int scancode, int action, int mod );

float x = 0.0f;
float y = 0.0f;
float inc = 0.5f;

int main()
{
    std::cout << "orthographic projection" << std::endl;
    std::cout << "arrows to move projection" << std::endl;

    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    GLFWwindow* window = glfwCreateWindow( 600, 600, "ortho", nullptr, nullptr );
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
    
    unsigned int VAO, VBO, EBO;
    
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
        
        glm::mat4 orthographic = glm::ortho( x, x + 5.0f, y, y + 5.0f, -1.0f, 1.0f );       
        glm::mat4 model = glm::translate( glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 0.0f) );
        
        shaderProgram.setUniformMat4fv( "ortho", orthographic );
        shaderProgram.setUniformMat4fv( "model", model );

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
    glViewport( 0, 0, 600, 600 );
}

void key_callback( GLFWwindow* window, int key, int scancode, int action, int mod )
{
    if( action == GLFW_PRESS )
    {
        if( key == GLFW_KEY_ESCAPE )
            glfwSetWindowShouldClose( window, true );
        
        if( key == GLFW_KEY_LEFT )
            x -= inc;
        if( key == GLFW_KEY_RIGHT )
            x += inc;
        if( key == GLFW_KEY_UP )
            y += inc;
        if( key == GLFW_KEY_DOWN )
            y -= inc;
    
        std::cout << "x: " << x << std::endl;
        std::cout << "y: " << y << std::endl;
    }
}
