#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader/ShaderProgram.h>
#include <Texture/Texture.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void resize_callback( GLFWwindow* window, int width, int height );
void key_callback( GLFWwindow* window, int key, int scancode, int action, int mod );
void processInput( GLFWwindow* window );

unsigned int SCR_WIDTH = 600;
unsigned int SCR_HEIGHT = 600;

glm::vec3 cameraPos = glm::vec3( 0.0f, 0.0f, 4.0f );
glm::vec3 cameraFront = glm::vec3( 0.0f, 0.0f, -1.0f );
glm::vec3 cameraUp = glm::vec3( 0.0f, 1.0f, 0.0f );

float deltaTime = 0.0f;
float lastFrame = 0.0f;

const float cameraSpeed = 2.5f;

int main()
{
    std::cout << "basic camera movement" << std::endl;
    std::cout << "WASD = move" << std::endl;

    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    GLFWwindow* window = glfwCreateWindow( SCR_WIDTH, SCR_HEIGHT, "camera-2", nullptr, nullptr );
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
    glViewport( 0, 0, SCR_WIDTH, SCR_HEIGHT );

    ShaderProgram shaderProgram( VERTEX_SHADER, FRAGMENT_SHADER );
    shaderProgram.link();
    shaderProgram.use();
    
    shaderProgram.setUniform1i( "texture0", 0 );
    shaderProgram.setUniform1i( "texture1", 1 );
    
    glActiveTexture( GL_TEXTURE0 );
    Texture container( CONTAINER_JPG );
    container.load( GL_RGB, GL_RGB );

    glActiveTexture( GL_TEXTURE1 );
    Texture face( FACE_PNG );
    face.load( GL_RGBA, GL_RGBA );
    
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    
    unsigned int VAO, VBO;

    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );

    glBindVertexArray( VAO );
    
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*) 0 );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*) (3*sizeof(float)) );

    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );

    glEnable( GL_DEPTH_TEST );
    
    while( !glfwWindowShouldClose(window) )
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput( window );

        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glm::mat4 model = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.5f, 0.4f, 0.2f) );
        glm::mat4 projection = glm::perspective( glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f );
        glm::mat4 view = glm::lookAt( cameraPos, cameraPos + cameraFront, cameraUp );
        
        shaderProgram.setUniformMat4fv( "view", view );
        shaderProgram.setUniformMat4fv( "model", model );
        shaderProgram.setUniformMat4fv( "projection", projection );
        
        glBindVertexArray( VAO );
        glDrawArrays( GL_TRIANGLES, 0, 36 );

        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    glDeleteBuffers( 1, &VBO );
    glDeleteVertexArrays( 1, &VAO );
    glfwTerminate();
    
    return 0;
}

void resize_callback( GLFWwindow* window, int width, int height )
{
    glViewport( 0, 0, width, height );
}

void key_callback( GLFWwindow* window, int key, int scancode, int action, int mod )
{
    if( action == GLFW_PRESS )
    {
        if( key == GLFW_KEY_ESCAPE )
            glfwSetWindowShouldClose( window, true );
    }
}

void processInput( GLFWwindow* window )
{
    if( glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS )
        cameraPos += cameraSpeed * cameraFront * deltaTime;
    if( glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS )
        cameraPos -= cameraSpeed * cameraFront * deltaTime;
    if( glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS )
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
    if( glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS )
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
}
