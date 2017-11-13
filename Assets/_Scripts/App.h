#ifndef APP_H
#define APP_H

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 360
#define WINDOW_RESIZE false
#define APP_NAME "Math Assignment"

#include "GUI.h"
#include "Mat4x4.h"
#include "EntryWidget.h"

struct OperatorButton
{
  const char* label;
  GtkWidget* button;
};

struct InputFieldButton
{
  GtkWidget* button;
  int width = 5;
  int x = 0;
  int y = 0;
};


class App
{
  private: GtkWidget* window;
  private: GtkWidget* fixed;
  private: GUI* gui;

  private: EntryWidget* entry;

  private: OperatorButton* buttons;

  private: InputFieldButton* inputfieldButtons;

  private: const gchar* styleSheetPath = "MathAssignment/stylesheet.css";

  private: int rows = 4;
  private: int colums = 4;
  private: int xPos = 10;
  private: int yPos = 10;
  private: int increment = 32;

  public: App(int argc, char* argv[])
  {
    gui = new GUI();
    entry = new EntryWidget();
    buttons = new OperatorButton[4];
    inputfieldButtons = new InputFieldButton[rows*colums];
    gtk_init(&argc, &argv);
  }

  public: void showApp()
  {
    this->window = gui->createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_RESIZE, APP_NAME, 10);
    this->fixed = gui->createFixed(this->window);

    generateButtons();

    gui->setStyleSheet(styleSheetPath);

    gtk_widget_show_all(window);
    gtk_main();
  }

  private: void generateButtons()
  {
    GtkWidget* b = entry->create(this->fixed, 10,10,20,20,"0",false);

    entry->reset((GtkEntry*)b);
    //t(xPos,yPos,increment);
/*
    buttons[0].label = "+";
    buttons[0].button = gui->createButton("+", this->fixed, 290, 10, 20, 20);

    buttons[1].label = "-";
    buttons[1].button = gui->createButton("-", this->fixed, 290, 50, 20, 20);

    buttons[2].label = "*";
    buttons[2].button = gui->createButton("*", this->fixed, 290, 90, 20, 20);

    buttons[3].label = "=";
    buttons[3].button = gui->createButton("=", this->fixed, 290, 130, 20, 20);
    */

  }

  private: void t(int startXPos,int startYPos,int increment)
  {
    int index = 0;
    int x = startXPos;
    int y = startYPos;
    int inc = increment;

    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < colums; j++)
      {
        inputfieldButtons[i].button = gui->createInputField("0",this->fixed, x, y, inputfieldButtons[i].width,10);
        index++;
        x += inc*2 + inputfieldButtons[i].width;

        if(index >= rows)
        {
          y += inc+10;
          index = 0;
          x = startXPos;
        }
        inputfieldButtons[i].x = x;
        inputfieldButtons[i].y = y;
      }
    }
  }

  public: ~App()
  {
    gtk_main_quit();
  }
};
#endif
