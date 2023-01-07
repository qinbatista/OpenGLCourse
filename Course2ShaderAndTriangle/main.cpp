#include "GL/glew.h"
#include "InternalLibs/GLFWManager.h"
#include "InternalLibs/GLEWManager.h"
int main()
{
    InitGLEW(InitGLFW(),GLFWGetWidth(), GLFWGetHeight());
    return 0;
}