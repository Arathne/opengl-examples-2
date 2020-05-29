#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader/Shader.h>
#include <string>

class ShaderProgram
{
    private:
        unsigned int programID;
        Shader* vertexShader;
        Shader* fragmentShader;

        ShaderProgram (void);

    public:
        ShaderProgram (std::string vertexFile, std::string fragmentFile);
        ~ShaderProgram (void);
        
        void link (void) const;
        void use (void) const;
};

#endif
