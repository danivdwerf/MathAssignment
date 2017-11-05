#ifndef APP_H
#define APP_H

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 360
#define WINDOW_RESIZE false
#define APP_NAME "Math Assignment"

#include "GUI.h"
#include "Mat4x4.h"

struct OperatorButton
{
  const char* label;
  GtkWidget* button;
};

class App
{
  private: GtkWidget* window;
  private: GtkWidget* fixed;
  private: GUI* gui;
  private: OperatorButton* buttons;

  public: App(int argc, char* argv[])
  {
    gui = new GUI();

    buttons = new OperatorButton[4];

    gtk_init(&argc, &argv);
  }

  public: void showApp()
  {
    this->window = gui->createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_RESIZE, APP_NAME, 10);
    this->fixed = gui->createFixed(this->window);

    buttons[0].label = "+";
    buttons[0].button = gui->createButton("+", this->fixed, 20, 20, 20, 20);

    buttons[1].label = "-";
    buttons[1].button = gui->createButton("-", this->fixed, 20, 60, 20, 20);

    buttons[2].label = "*";
    buttons[2].button = gui->createButton("*", this->fixed, 20, 100, 20, 20);

    buttons[3].label = "=";
    buttons[3].button = gui->createButton("=", this->fixed, 20, 140, 20, 20);

    gtk_widget_show_all(window);
    gtk_main();
  }

  public: ~App()
  {
    gtk_main_quit();
  }
};
#endif
