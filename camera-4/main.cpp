#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader/ShaderProgram.h>
#include <Texture/Texture.h>
#include <Camera/Camera.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void resize_callback( GLFWwindow* window, int width, int height );
void key_callback( GLFWwindow* window, int key, int scancode, int action, int mod );
void mouse_callback( GLFWwindow* window, double xMousePos, double yMousePos );
void processInput( GLFWwindow* window );

unsigned int SCR_WIDTH = 600;
unsigned int SCR_HEIGHT = 600;

Camera freecam( glm::vec3(0.0f, 0.0f, 4.0f) );
float deltaTime = 0.0f;
double lastX = 600.0f;
double lastY = 600.0f;

int main()
{
    std::cout << "camera class to handle movement" << std::endl;
    std::cout << "WASD = move" << "\n" << "MOUSE = rotate camera" << std::endl;

    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    GLFWwindow* window = glfwCreateWindow( SCR_WIDTH, SCR_HEIGHT, "camera-4", nullptr, nullptr );
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

    glViewport( 0, 0, SCR_WIDTH, SCR_HEIGHT );
    glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

    glfwSetFramebufferSizeCallback( window, resize_callback );
    glfwSetKeyCallback( window, key_callback );
    glfwSetCursorPosCallback( window, mouse_callback );

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
    
    glfwSwapInterval( 0 );
    
    float lastFrame = 0.0f;

    while( !glfwWindowShouldClose(window) )
    {
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        processInput( window );
        
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        glm::mat4 model = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.5f, 0.4f, 0.2f) );
        glm::mat4 view = freecam.getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 600.0f/600.0f, 0.1f, 100.0f);
        
        shaderProgram.setUniformMat4fv( "model", model );
        shaderProgram.setUniformMat4fv( "view", view );
        shaderProgram.setUniformMat4fv( "projection", projection );

        glBindVertexArray( VAO );
        glDrawArrays( GL_TRIANGLES, 0, 36 );
        
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

void key_callback( GLFWwindow* window, int key, int scancode, int action, int mod )
{
    if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
        glfwSetWindowShouldClose(window, true);
}

bool firstMouse = true;
void mouse_callback( GLFWwindow* window, double xMousePos, double yMousePos )
{
    if( firstMouse )
    {
        lastX = xMousePos;
        lastY = yMousePos;
        firstMouse = false;
    }

    float xOffset = xMousePos - lastX;
    float yOffset = lastY - yMousePos;

    lastX = xMousePos;
    lastY = yMousePos;
    freecam.mouse( xOffset, yOffset );
}

void processInput( GLFWwindow* window )
{
    if( glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS )
        freecam.keyboard( FORWARD, deltaTime );
    if( glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS )
        freecam.keyboard( BACKWARD, deltaTime );
    if( glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS )
        freecam.keyboard( LEFT, deltaTime );
    if( glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS )
        freecam.keyboard( RIGHT, deltaTime );
}
