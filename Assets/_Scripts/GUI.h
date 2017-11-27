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

  public: GtkWidget* createInputField(const char* text, GtkWidget* fixed, int xPos, int yPos, int width,int h, const char* id = "InputField")
  {
    GtkWidget* temp = gtk_entry_new();
    gtk_entry_set_placeholder_text((GtkEntry*)temp, text);
    gtk_entry_set_width_chars((GtkEntry*)temp, width);

    gtk_fixed_put (GTK_FIXED (fixed), temp, xPos, yPos);
    gtk_widget_set_name(temp, id);
    return temp;
  }

  public: const char* getEntryText(GtkWidget* entry)
  {
    const char* entryText = gtk_entry_get_text(GTK_ENTRY(entry));
    return entryText;
  }

  public: void setStyleSheet(const gchar* path)
  {
    GtkCssProvider* provider = gtk_css_provider_new();
    GdkDisplay* display = gdk_display_get_default();
    GdkScreen* screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    GError* error = nullptr;
    gtk_css_provider_load_from_file(provider, g_file_new_for_path(path), &error);

    if(error != NULL)
      std::cout << error-> message << '\n';

    g_object_unref(provider);
  }

};
#endif
