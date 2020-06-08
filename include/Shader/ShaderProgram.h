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
        int currentUniform;

        ShaderProgram (void);

    public:
        ShaderProgram (std::string vertexFile, std::string fragmentFile);
        ~ShaderProgram (void);
        
        void link (void) const;
        void use (void) const;
        
        bool getUniform (std::string name);
        void setUniform1f (float value) const;
        void setUniform4f (float x, float y, float z, float a) const;
        void setUniform1i (int value) const;

};

#endif
