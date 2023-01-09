
#include "GL/glew.h"
#include "Class/DisplaySystem.h"
#include "InternalLibs/Window.h"
#include "glm/gtc/matrix_transform.hpp"
#include "InternalLibs/Camera.h"
Window mainWindow;
DisplaySystem displaySystem;
Camera camera;
GLfloat now,deltaTime,lastTime;
int main()
{
    mainWindow = Window(800, 600);
    mainWindow.Initialise();
    displaySystem = DisplaySystem(mainWindow.getBufferWidth() / mainWindow.getBufferHeight());
    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 1.0, 0.1f);
    displaySystem.Awake(&camera);
    while (!mainWindow.getShouldClose())
    {
        //time setting
        now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;
        // Get and handle user input events
        glfwPollEvents();
        //Camera view
        camera.keyControl(mainWindow.getKeys(), deltaTime);
        camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
        // Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        displaySystem.Update();
        // Swap buffers
        mainWindow.swapBuffers();
    }
    return 0;
}