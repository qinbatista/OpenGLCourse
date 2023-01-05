#ifndef GLFWManager
#define GLFWManager
#include "GLFW/glfw3.h"
const GLint WIDTH = 800, HEIGHT = 600;
GLFWwindow *InitGLFW();
GLint GLFWGetWidth();
GLint GLFWGetHeight();
#endif