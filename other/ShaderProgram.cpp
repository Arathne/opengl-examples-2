#include <Shader/ShaderProgram.h>
#include <iostream>

ShaderProgram::ShaderProgram (std::string vertexFile, std::string fragmentFile) 
{
    programID = glCreateProgram();
    currentUniform = -1;

    vertexShader = new Shader( GL_VERTEX_SHADER, vertexFile );
    fragmentShader = new Shader( GL_FRAGMENT_SHADER, fragmentFile );

    vertexShader-> compile();
    fragmentShader-> compile();

    vertexShader-> attach( programID );
    fragmentShader-> attach( programID );
}

ShaderProgram::~ShaderProgram (void)
{
    if( vertexShader != nullptr )
        delete vertexShader;

    if( fragmentShader != nullptr )
        delete fragmentShader;

    glDeleteProgram( programID );
}

void ShaderProgram::link (void) const
{
    glLinkProgram( programID );
}

void ShaderProgram::use (void) const
{
    glUseProgram( programID );
}

bool ShaderProgram::getUniform (std::string name)
{
    bool success = true;
    currentUniform = glGetUniformLocation( programID, name.c_str() );
    
    if( currentUniform < 0 )
        success= false;
    
    return success;
}

void ShaderProgram::setUniform1f (float value) const
{
    ShaderProgram::use();
    glUniform1f( currentUniform, value );
}

void ShaderProgram::setUniform4f (float x, float y, float z, float a) const
{
    ShaderProgram::use();
    glUniform4f( currentUniform, x, y, z, a );
}

void ShaderProgram::setUniform1i (int value) const
{
    glUniform1i( currentUniform, value );
}

void ShaderProgram::setUniform1i (std::string name, int value)
{
    ShaderProgram::getUniform( name );
    ShaderProgram::setUniform1i( value );
}

void ShaderProgram::setUniformMat4fv (glm::mat4 matrix) const
{
    glUniformMatrix4fv( currentUniform, 1, GL_FALSE, glm::value_ptr(matrix) );
}

void ShaderProgram::setUniformMat4fv (std::string name, glm::mat4 matrix)
{
    ShaderProgram::getUniform( name );
    ShaderProgram::setUniformMat4fv( matrix );
}

void ShaderProgram::setUniformVec2fv (glm::vec2 vector, int count) const
{
    glUniform2fv( currentUniform, count, glm::value_ptr(vector) );
}
