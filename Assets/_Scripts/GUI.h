#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>

class GUI
{
  public: GtkWidget* createWindow(int width, int height, bool rezisable, const char* title, int borderwidth, const char* id = "window")
  {
   	GtkWidget* temp = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   	gtk_widget_set_size_request(temp, width, height);
   	gtk_window_set_resizable(GTK_WINDOW(temp), rezisable);
   	gtk_window_set_title(GTK_WINDOW(temp), title);
   	gtk_container_set_border_width (GTK_CONTAINER(temp), borderwidth);
    gtk_window_set_position(GTK_WINDOW(temp), GTK_WIN_POS_CENTER);
  	g_signal_connect(temp, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_set_name(temp, id);
  	return temp;
  }

  public: GtkWidget* createFixed(GtkWidget* window)
  {
  	GtkWidget* temp = gtk_fixed_new ();
  	gtk_container_add (GTK_CONTAINER (window), temp);
  	return temp;
  }

  public: GtkWidget* createButton(const char* label, GtkWidget* fixed, int xPos, int yPos, int width, int height, const char* id = "button")
  {
   	GtkWidget* temp = gtk_button_new_with_label (label);
    gtk_widget_set_size_request(temp, width, height);
  	gtk_fixed_put (GTK_FIXED (fixed), temp, xPos, yPos);
    gtk_widget_set_name(temp, id);
  	return temp;
  }
};
#endif
