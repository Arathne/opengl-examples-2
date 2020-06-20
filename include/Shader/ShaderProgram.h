#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader/Shader.h>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
        void setUniform1i (std::string name, int value);
        void setUniformMat4fv (glm::mat4 matrix) const;
        void setUniformMat4fv (std::string name, glm::mat4 matrix);
        void setUniformVec2fv (glm::vec2 vector, int count) const;
};

#endif
