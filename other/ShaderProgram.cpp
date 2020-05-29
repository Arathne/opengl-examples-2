#include <Shader/ShaderProgram.h>
#include <iostream>

ShaderProgram::ShaderProgram (void) {}

ShaderProgram::~ShaderProgram (void) {}

void ShaderProgram::say_hello (void) const
{
    std::cout << "HELLO WORLD!?" << std::endl;
}
