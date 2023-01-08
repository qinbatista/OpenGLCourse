#pragma once
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
class Shader
{
public:
    Shader();
    void CreateFromString(const char *vertexCode, const char *fragmentCode);
    void CreateFromFiles(const char *vertexLocation, const char *fragmentLocation);
    std::string ReadFile(const char *fileLocation);
    GLuint GetProjectionLocation();
    GLuint GetModelLocation();
    GLuint GetViewLocation();
    void UseShader();
    void ClearShader();
    void AddShader(GLuint theProgram, const char *shaderCode, GLenum shaderType);
    ~Shader();
private:
    GLuint shaderID, uniformProjection, uniformModel, uniformView;//, uniformView;
    void CompileShader(const char *vertexCode, const char *fragmentCode);
};
