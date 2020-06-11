#include <Texture/Texture.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture (void) {}

Texture::Texture (std::string file)
{
    this-> file = file;
    glGenTextures( 1, &id );
    stbi_set_flip_vertically_on_load( true );
    data = stbi_load( file.c_str(), &width, &height, &channels, 0 );
}

Texture::~Texture (void)
{
    if( data == nullptr )
        delete[] data;
}

void Texture::load (unsigned int image_rgb, unsigned int opengl_rgb) const
{
    Texture::bind();

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    if( data == nullptr )
        throw std::runtime_error( "Failed to load texture :: " + file );

    glTexImage2D( GL_TEXTURE_2D, 0, image_rgb, width, height, 0, opengl_rgb, GL_UNSIGNED_BYTE, data );
    glGenerateMipmap( GL_TEXTURE_2D );
}

void Texture::bind (void) const
{
    glBindTexture( GL_TEXTURE_2D, id );
}
