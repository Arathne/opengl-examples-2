#include <Shader/ShaderProgram.h>
#include <iostream>

ShaderProgram::ShaderProgram (std::string vertexFile, std::string fragmentFile) 
{
    programID = glCreateProgram();

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
