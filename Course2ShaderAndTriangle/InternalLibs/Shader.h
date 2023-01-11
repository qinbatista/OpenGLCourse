#pragma once
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
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
    GLuint GetAmbientIntensityLocation();
    GLuint GetAmbientColorLocation();
    void UseShader();
    void ClearShader();
    void AddShader(GLuint theProgram, const char *shaderCode, GLenum shaderType);
    ~Shader();

private:
    GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformAmbientIntensity, uniformAmbientColor; //, uniformView;
    void CompileShader(const char *vertexCode, const char *fragmentCode);
};
