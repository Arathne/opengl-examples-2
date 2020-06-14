#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader/ShaderProgram.h>
#include <Texture/Texture.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void resize_callback( GLFWwindow* window, int width, int height );
void key_callback( GLFWwindow* window, int key, int scancode, int action, int mod );

int SCR_WIDTH = 600;
int SCR_HEIGHT = 600;

float FOV = 45;

int main()
{   
    std::cout << "persepective using model, view, projection matrix" << std::endl;
    std::cout << "UP = increase field of view by 5"<< std::endl;
    std::cout << "DOWN = decrease field of view by 5"<< std::endl;

    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    
    GLFWwindow* window = glfwCreateWindow( SCR_WIDTH, SCR_HEIGHT, "transform-3", nullptr, nullptr );
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
    
    glfwSetFramebufferSizeCallback( window, resize_callback );
    glfwSetKeyCallback( window, key_callback );
    
    ShaderProgram shaderProgram( VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH );
    shaderProgram.link();
    shaderProgram.use();
    
    shaderProgram.getUniform( "texture1" );
    shaderProgram.setUniform1i( 0 );
    shaderProgram.getUniform( "texture2" );
    shaderProgram.setUniform1i( 1 );
    
    glActiveTexture( GL_TEXTURE0 );
    Texture container( CONTAINER_JPG );
    container.load( GL_RGB, GL_RGB );

    glActiveTexture( GL_TEXTURE1 );
    Texture face( FACE_PNG );
    face.load( GL_RGBA, GL_RGBA );

    float vertices[] = {
        0.5f,  0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 1.0f, 0.0f,
       -0.5f, -0.5f, 0.0f, 0.0f,
       -0.5f,  0.5f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
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
    
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*) 0 );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*) (2*sizeof(float)) );

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    while( !glfwWindowShouldClose(window) )
    {
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );
        
        glm::mat4 model = glm::mat4( 1.0f );
        glm::mat4 view = glm::mat4( 1.0f );
        glm::mat4 projection = glm::mat4( 1.0f );

        model = glm::rotate( model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f) );
        view = glm::translate( view, glm::vec3(0.0f, 0.0f, -3.0f) );
        projection = glm::perspective( glm::radians(FOV), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f );

        shaderProgram.setUniformMat4fv( "model", model );
        shaderProgram.setUniformMat4fv( "view", view );
        shaderProgram.setUniformMat4fv( "projection", projection );

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
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    glViewport( 0, 0, width, height );
}

void key_callback( GLFWwindow* window, int key, int scancode, int action, int mod )
{
    if( action == GLFW_PRESS )
    {
        if( key == GLFW_KEY_ESCAPE )
        {
            glfwSetWindowShouldClose(window, true);
        }
        if( key == GLFW_KEY_UP )
        {
            FOV += 5;
            std::cout << "FOV: " << FOV << std::endl;   
        }
        else if( key == GLFW_KEY_DOWN && FOV > 0 )
        {
            FOV -= 5;
            std::cout << "FOV: " << FOV << std::endl;   
        }
    }
}
