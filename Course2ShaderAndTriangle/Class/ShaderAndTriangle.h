#ifndef ShaderAndTriangle
#define ShaderAndTriangle
#include "GL/glew.h"
#include "glm/gtc/matrix_transform.hpp"
void DrawTriangle(glm::mat4 DisplayProjection, glm::mat4 calculateViewMatrix);
void CreateObjects();
void CreateShaders();
void AddShader(GLuint theProgram, const char *shaderCode, GLenum shaderType);
extern bool direction;
extern float triOffset;
extern float triMaxOffset;
extern float triIncrement;
#endif