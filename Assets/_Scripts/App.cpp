#include "App.h"

App::App()
{
  matrix->mat[0][2] = 4;
  matrix->mat[2][3] = 2;
  matrix->mat[1][2] = 6;
  matrix->mat[3][1] = 7;

  matrix2->mat[0][0] = 3;
  matrix2->mat[1][1] = 5;

  matrix * *matrix2;
  std::cout << matrix << '\n';

  setupGLFW();
  createWindow();

  while(!glfwWindowShouldClose(App::window))
  {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    this->update();

    glfwSwapBuffers(App::window);
    glfwPollEvents();
  }

  glfwDestroyWindow(App::window);
  glfwTerminate();
}

void App::setupGLFW()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void App::createWindow()
{
  App::window = glfwCreateWindow(windowWidth, windowHeight, APP_NAME, NULL, NULL);
  if (App::window == NULL)
  {
    std::cout << "Failed to create GLFW window" << '\n';
    glfwTerminate();
  }
  glfwMakeContextCurrent(App::window);
  // glfwSetFramebufferSizeCallback(App::window, onWindowResize);
  // glfwSetCursorPosCallback(window, onMouseMove);
  // glfwSetScrollCallback(window, onMouseScroll);
  // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void App::update()
{

}
