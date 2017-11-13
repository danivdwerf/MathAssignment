#ifndef ENTRY_WIDGET_H
#define ENTRY_WIDGET_H

#include <gtk/gtk.h>

class EntryWidget
{
  public: GtkWidget* create(GtkWidget* fixed , int xPos, int yPos, int width, int height, const char* text,bool center = false,const char* id = "EntryWidget")
  {
    GtkWidget* entry = gtk_entry_new();
    // gtk_entry_set_placeholder_text((GtkEntry*)entry, text);
    gtk_entry_set_text((GtkEntry*)entry,text);
    gtk_entry_set_width_chars((GtkEntry*)entry,width);
    gtk_fixed_put (GTK_FIXED (fixed), entry, xPos, yPos);
    gtk_widget_set_name(entry, id);

    if(center)
    {
      //TODO fix bug.
      gtk_entry_set_alignment ((GtkEntry*)entry , (width/2));
    }
    return entry;
  }

  // Fetch the data in the entry in string.
  public: std::string fetchData(GtkEntry* entry)
  {
    std::string str;
    str = gtk_entry_get_text (entry);
    std::cout << str << '\n';
    return str;
  }

  public: void reset(GtkEntry* entry)
  {
    gtk_entry_set_placeholder_text(entry,"0");
    gtk_entry_set_text(entry,"1");
  }

};
#endif
