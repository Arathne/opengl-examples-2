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
