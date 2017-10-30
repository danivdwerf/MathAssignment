#include <iostream>
#include "Assets/_Scripts/App.h"

App* app = nullptr;

int main(int argc, char* argv[])
{
  app = new App(argc, argv);
  app->showApp();
  return 0;
}
