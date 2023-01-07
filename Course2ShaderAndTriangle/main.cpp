#include "GL/glew.h"
#include "Class/DisplaySystem.h"
#include "InternalLibs/Window.h"
#include "glm/gtc/matrix_transform.hpp"
Window mainWindow;
DisplaySystem displaySystem;
int main()
{
    mainWindow = Window(800, 600);
    mainWindow.Initialise();
    displaySystem = DisplaySystem(mainWindow.getBufferWidth() / mainWindow.getBufferHeight());
    displaySystem.Awake();
    while (!mainWindow.getShouldClose())
    {
        // Get and handle user input events
        glfwPollEvents();
        // Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        displaySystem.Update();
        // Swap buffers
        mainWindow.swapBuffers();
    }
    return 0;
}