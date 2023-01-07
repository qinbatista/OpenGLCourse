#include "GL/glew.h"
#include "InternalLibs/DisplayManager.h"
#include "InternalLibs/Window.h"
#include "glm/gtc/matrix_transform.hpp"
Window mainWindow;
int main()
{
    // InitGLEW(InitGLFW(),GLFWGetWidth(), GLFWGetHeight());
    mainWindow = Window(800, 600);
    mainWindow.Initialise();
    Awake();
    while (!mainWindow.getShouldClose())
    {
        // Get and handle user input events
        glfwPollEvents();
        // Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Update();
        // Swap buffers
        mainWindow.swapBuffers();
    }
    return 0;
}