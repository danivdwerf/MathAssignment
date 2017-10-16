#ifndef APP_H
#define APP_H

#define windowWidth 640
#define windowHeight 360
#define APP_NAME "Math Assignment"

#include <iostream>
#include <GLFW/glfw3.h>

#include "Input.h"
#include "Mat4x4.h"

Mat4x4* matrix;
Mat4x4* matrix2;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

class App
{
  public: static GLFWwindow* window;
  public: App();

  public: void update();
  private: void setupGLFW();
  private: void createWindow();
};
#endif
