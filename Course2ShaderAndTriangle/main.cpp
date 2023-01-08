#include "GL/glew.h"
#include "Class/DisplaySystem.h"
#include "InternalLibs/Window.h"
#include "glm/gtc/matrix_transform.hpp"
#include "InternalLibs/Camera.h"
Window mainWindow;
DisplaySystem displaySystem;
Camera camera;
int main()
{
    mainWindow = Window(800, 600);
    mainWindow.Initialise();
    displaySystem = DisplaySystem(mainWindow.getBufferWidth() / mainWindow.getBufferHeight());
    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 0.001f, 1.0f);
    displaySystem.Awake();
    while (!mainWindow.getShouldClose())
    {
        // Get and handle user input events
        glfwPollEvents();
        camera.keyControl(mainWindow.getKeys(), 10);
        // Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        displaySystem.Update(camera);
        // Swap buffers
        mainWindow.swapBuffers();
    }
    return 0;
}