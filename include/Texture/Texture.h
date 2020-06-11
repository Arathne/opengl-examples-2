#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <stdexcept>

class Texture
{
    private:
        Texture (void);

        std::string file;
        unsigned int id;
        unsigned char* data;
        int width;
        int height;
        int channels;

    public:
        Texture (std::string file);
        ~Texture (void);
        
        void load (unsigned int image_rgb, unsigned int opengl_rgb) const;
        void bind (void) const;
};

#endif
