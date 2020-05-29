#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

class Shader
{
    private:
        unsigned int type;
        unsigned int shader;
        char* code;
        
        Shader (void);


    public:
        Shader (unsigned int type, std::string file);
        ~Shader (void);
        void attach (unsigned int program) const;
        void setCode (std::string file);
        void compile (void) const;
};

#endif
