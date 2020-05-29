#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <Shader/ShaderProgram.h>
#include <Shader/Shader.h>

void resize( GLFWwindow* window, int width, int height );
void processInput( GLFWwindow* window );

int main()
{
    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    GLFWwindow* window = glfwCreateWindow( 600, 600, "shader", nullptr, nullptr );
    if( window == nullptr )
    {
        glfwTerminate();
        std::cout << "Failed to create glfw window" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent( window );

    if( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport( 0, 0, 600, 600 );
    glfwSetFramebufferSizeCallback( window, resize );
    
    unsigned int shaderProgram;
    Shader vertexShader( GL_VERTEX_SHADER, VERTEX_SHADER_PATH );
    Shader fragmentShader( GL_FRAGMENT_SHADER, FRAGMENT_SHADER_PATH );
    shaderProgram = glCreateProgram();

    vertexShader.compile();
    fragmentShader.compile();
    
    vertexShader.attach( shaderProgram );
    fragmentShader.attach( shaderProgram );

    glLinkProgram( shaderProgram );
    glUseProgram( shaderProgram );
    
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray( VAO );

    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*) 0 );
    glEnableVertexAttribArray(0);

    while( !glfwWindowShouldClose(window) )
    {
        processInput( window );

        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );
        
        glUseProgram( shaderProgram );
        glBindVertexArray(VAO);
        glDrawArrays( GL_TRIANGLES, 0, 3 );

        glfwSwapBuffers( window );
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}


void resize( GLFWwindow* window, int width, int height ) 
{
    glViewport( 0, 0, width, height );
}

void processInput( GLFWwindow* window ) 
{
    if( glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS )
    {
        glfwSetWindowShouldClose(window, true);
    }
}
