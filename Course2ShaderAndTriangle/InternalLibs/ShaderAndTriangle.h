#ifndef ShaderAndTriangle
#define ShaderAndTriangle
#include "GL/glew.h"
void DrawTriangle();
void CreateObjects();
void CreateShaders();
void AddShader(GLuint theProgram, const char *shaderCode, GLenum shaderType);
extern bool direction;
extern float triOffset;
extern float triMaxOffset;
extern float triIncrement;
#endif