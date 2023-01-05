#include "GL/glew.h"
#include "GLFWManager.h"
#include "ShaderAndTriangle.h"
#include "GLEWManager.h"
#include <stdio.h>
#include <string.h>
// Window dimensions
GLuint VAO, VBO, Shader;
GLFWwindow* mainWindow;
int main()
{
    mainWindow = InitGLFW();
    InitGLEW(mainWindow,GLFWGetWidth(), GLFWGetHeight());
    return 0;
}