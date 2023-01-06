#include "GL/glew.h"
#include "InternalLibs/GLFWManager.h"
#include "InternalLibs/GLEWManager.h"
GLFWwindow* mainWindow;
int main()
{
    mainWindow = InitGLFW();
    InitGLEW(mainWindow,GLFWGetWidth(), GLFWGetHeight());
    return 0;
}