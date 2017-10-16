#include "Input.h"

Input::Input(GLFWwindow* window)
{
  this->window = window;
}

bool Input::getKeyDown(KeyCode keyCode)
{
  if (glfwGetKey(this->window, keyCode) == GLFW_PRESS)
    return true;

  return false;
}
