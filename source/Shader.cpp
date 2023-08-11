#include "Shader.h"

Shader::Shader(const std::string &_vertexFilePath, const std::string &_fragmentFilePath) {
    CompileShader(ReadFile(_vertexFilePath), ReadFile(_fragmentFilePath));
}

Shader::~Shader() { ClearShader(); };

std::string Shader::ReadFile(const std::string &_filePath) {
    std::string content;
    std::fstream fileStream(_filePath, std::ios::in);

    if ( !fileStream.is_open() ) {
        std::cerr << "Fail to read " << _filePath << " file" << std::endl;
        return "";
    }

    std::string line;

    while ( !fileStream.eof() ) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();

    return content;
}

GLuint Shader::GetUniformLocation(const std::string& _name) const { return glGetUniformLocation(shaderID, _name.c_str()); }

void Shader::UseShader() const { glUseProgram(shaderID); }

void Shader::ClearShader() const {
    if ( shaderID != 0 ) glDeleteProgram(shaderID);
}

void Shader::CompileShader(const std::string& _vertexCode, const std::string& _fragmentCode) {
    shaderID = glCreateProgram();

    if ( !shaderID ) {
        std::cerr << "Error creating shader program" << std::endl;
        return ;
    }

    AddShader(shaderID, _vertexCode, GL_VERTEX_SHADER);
    AddShader(shaderID, _fragmentCode, GL_FRAGMENT_SHADER);

    glLinkProgram(shaderID);

    GLint result;
    GLchar eLog[1024];

    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);

    if ( !result ) {
        glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
        std::cerr << "Error linking program: " << eLog << std::endl;
        return ;
    }

    glValidateProgram(shaderID);
    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);

    if ( !result ) {
        glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
        std::cerr << "Error validating program: " << eLog << std::endl;
        return ;
    }
}

void Shader::AddShader(GLuint _program, const std::string& _shaderCode, GLenum _shaderType) {
    GLuint shader = glCreateShader(_shaderType);

    const GLchar* shaderCode = _shaderCode.c_str();
    GLint codeLenght = _shaderCode.length();

    glShaderSource(shader, 1, &shaderCode, &codeLenght);
    glCompileShader(shader);

    GLint result;
    GLchar eLog[1024];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

    if ( !result ) {
        glGetShaderInfoLog(shader, sizeof(eLog), nullptr, eLog);
        std::cerr << "Error compiling " << shader << " shader: " <<  eLog << std::endl;
        return ;
    }

    glAttachShader(_program, shader);
}