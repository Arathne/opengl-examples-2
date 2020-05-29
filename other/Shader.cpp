#include <Shader/Shader.h>

Shader::Shader (unsigned int type, std::string file)
{
    this-> type = type;
    this-> shader = glCreateShader( type );
    Shader::setCode( file );
}

Shader::~Shader ()
{
    if( code != nullptr )
        delete[] code;

    if( shader != -1 )
        glDeleteShader( shader );
}

void Shader::setCode (std::string file)
{
    std::ifstream input( file );
    std::stringstream buffer;
    buffer << input.rdbuf();
    input.close();
    
    std::string strCode = buffer.str();
    this-> code = new char[ strCode.length()+1 ];
    std::strcpy( code, strCode.c_str() );
}

void Shader::compile (void) const
{
    glShaderSource( shader, 1, &code, nullptr );
    glCompileShader( shader );

    char infoLog[512];
    int success;

    glGetShaderiv( shader, GL_COMPILE_STATUS, &success );
    if( !success )
    {
        glGetShaderInfoLog( shader, 512, nullptr, infoLog );
        std::cout << "ERROR::SHADER::COMPILATION::FAILED\n" << infoLog << std::endl;
    }
}

void Shader::attach (unsigned int program) const
{
    glAttachShader( program, shader );
}
