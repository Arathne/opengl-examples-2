#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader/ShaderProgram.h>
#include <iostream>
#include <cmath>

void resize_callback( GLFWwindow* window, int width, int height );
void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods );

int main()
{
    std::cout << "uniform in shader" << std::endl;

    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    GLFWwindow* window = glfwCreateWindow( 600, 600, "shader-3", nullptr, nullptr );
    if( window == nullptr )
    {
        glfwTerminate();
        std::cout << "Failed to create glfw window" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent( window );
    if( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ))
    {
        glfwTerminate();
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport( 0, 0, 600, 600 );
    glfwSetFramebufferSizeCallback( window, resize_callback );
    glfwSetKeyCallback( window, key_callback );

    ShaderProgram shaderProgram( VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH );
    shaderProgram.link();

    float vertices[] = {
        0.5f, -0.5f,  0.0f,
       -0.5f, -0.5f,  0.0f,
        0.0f,  0.5f,  0.0f
    };

    unsigned int VBO, VAO;

    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );

    glBindVertexArray( VAO );
    
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*) 0 );
    glEnableVertexAttribArray( 0 );
    
    shaderProgram.getUniform( "newColor" );

    while( !glfwWindowShouldClose(window) )
    {
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );
        
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        float blueValue = cos(timeValue) / 2.0f + 0.5f;
        float redValue = -(cos(timeValue*2)) / 2.0f + 0.5f;
        shaderProgram.setUniform4f( redValue, greenValue, blueValue, 1.0f );

        shaderProgram.use();
        glBindVertexArray( VAO );
        glDrawArrays( GL_TRIANGLES, 0, 3 );

        glfwSwapBuffers( window );
        glfwPollEvents();
    }
    
    glDeleteVertexArrays( 1, &VAO );
    glDeleteBuffers( 1, &VBO );
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
