#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

class Shader {
    public:
        Shader(const std::string &_vertexFilePath, const std::string &_fragmentFilePath);
        ~Shader();
        static std::string ReadFile(const std::string& _filePath);
        GLuint GetUniformLocation(const std::string& _name) const;
        void UseShader() const;
        void ClearShader() const;

    private:
        GLuint shaderID{};
        void CompileShader(const std::string& _vertexCode, const std::string& _fragmentCode);
        void AddShader(GLuint _program, const std::string& _shaderCode, GLenum _shaderType) const;
};

#endif
