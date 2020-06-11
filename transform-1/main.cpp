#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader/ShaderProgram.h>
#include <Texture/Texture.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void resize_callback( GLFWwindow* window, int width, int height );
void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods );

bool option1 = true;

int main()
{
    std::cout << "rotating, translating, and scaling a square using a 4x4 matrix uniform" << std::endl;

    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    GLFWwindow* window = glfwCreateWindow( 600, 600, "transform-1", nullptr, nullptr );
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
    
    ShaderProgram shaderProgram( VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH );
    shaderProgram.link();
    shaderProgram.use();
    
    shaderProgram.getUniform("texture1");
    shaderProgram.setUniform1i( 0 );
    shaderProgram.getUniform("texture2");
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
       -0.5f,  0.5f, 0.0f, 1.0f,
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

    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    
    while( !glfwWindowShouldClose(window) )
    {
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );
        
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::scale( transform, glm::vec3(0.5f, 0.5f, 0.5f) );
        
        if( option1 )
        {
            transform = glm::translate( transform, glm::vec3(0.5f, 0.5f, 0.0f) );
            transform = glm::rotate( transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f) );
        }
        else
        {
            transform = glm::rotate( transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f) );
            transform = glm::translate( transform, glm::vec3(0.5f, 0.5f, 0.0f) );
        }

        shaderProgram.getUniform("transform");
        shaderProgram.setUniformMat4fv( transform );
        
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

void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
    if( action == GLFW_PRESS )
    {
        if( key == GLFW_KEY_ESCAPE )
        {
            glfwSetWindowShouldClose( window, true );
        }
        if( key == GLFW_KEY_ENTER )
        {
            option1 = !option1;
            if(option1)
                std::cout << "translate then rotate" << std::endl;
            else
                std::cout << "rotate then translate" << std::endl;
        }
    }
}
