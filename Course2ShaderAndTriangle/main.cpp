#include "GL/glew.h"
#include "InternalLibs/GLFWManager.h"
#include "InternalLibs/GLEWManager.h"
#include <stdio.h>
#include <string.h>
GLFWwindow* mainWindow;
int main()
{
    // CreateTriangle();
    mainWindow = InitGLFW();
    InitGLEW(mainWindow,GLFWGetWidth(), GLFWGetHeight());
    return 0;
}