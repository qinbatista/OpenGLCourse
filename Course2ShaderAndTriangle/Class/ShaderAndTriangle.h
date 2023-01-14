#ifndef ShaderAndTriangle
#define ShaderAndTriangle
#include "GL/glew.h"
#include "glm/gtc/matrix_transform.hpp"
#include "../InternalLibs/Camera.h"
void DrawTriangle(glm::mat4 DisplayProjection,  Camera *camera);
void CreateObjects();
void CreateShaders();
void AddShader(GLuint theProgram, const char *shaderCode, GLenum shaderType);
extern bool direction;
extern float triOffset;
extern float triMaxOffset;
extern float triIncrement;
#endif