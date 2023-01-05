#ifndef ShaderAndTriangle
#define ShaderAndTriangle
#include "GL/glew.h"
GLuint VAO, VBO, _shader;
void DrawTriangle();
void CreateTriangle();
void CompileShaders();
void AddShader(GLuint theProgram, const char *shaderCode, GLenum shaderType);
#endif