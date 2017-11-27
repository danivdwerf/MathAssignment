#ifndef ENTRY_WIDGET_H
#define ENTRY_WIDGET_H

#include <gtk/gtk.h>
#include <string>

class EntryWidget
{
  private: GtkWidget* widget = nullptr;

  public: EntryWidget(GtkWidget* fixed , int xPos, int yPos, int width, int height, const char* placeholder, bool center = false, const char* id = "EntryWidget")
  {
    GtkWidget* temp = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(temp), placeholder);
    gtk_entry_set_width_chars(GTK_ENTRY(temp), width);
    gtk_fixed_put (GTK_FIXED(fixed), temp, xPos, yPos);
    gtk_widget_set_name(temp, id);

    if(center)
    {
      //TODO fix bug.
      gtk_entry_set_alignment (GTK_ENTRY(temp) , (width/2));
    }

    this->widget = temp;
  }

  // Fetch the data in the entry in string.
  public: const char* getText()
  {
    const char* str = gtk_entry_get_text(GTK_ENTRY(this->widget));
    return str;
  }

  public: void setText(const char* value)
  {
    gtk_entry_set_text(GTK_ENTRY(this->widget), value);
  }

  public: void reset()
  {
    gtk_entry_set_text(GTK_ENTRY(this->widget), "");
    gtk_entry_set_placeholder_text(GTK_ENTRY(this->widget), "0");
  }

};
#endif
