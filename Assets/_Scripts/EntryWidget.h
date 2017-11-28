#ifndef ENTRY_WIDGET_H
#define ENTRY_WIDGET_H

#include <gtk/gtk.h>
#include <string>

class EntryWidget
{
  public: GtkWidget* widget = nullptr;

  public: EntryWidget(int w, int h, const char* placeholder, int marginL, int marginT, const char* id = "EntryWidget")
  {
    GtkWidget* temp = gtk_text_view_new ();
    gtk_text_view_set_left_margin (GTK_TEXT_VIEW(temp), marginL);
    gtk_text_view_set_top_margin (GTK_TEXT_VIEW(temp), marginT);

    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(temp));
    gtk_text_buffer_set_text(buffer, placeholder, -1);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(temp), true);
    gtk_widget_set_size_request(temp, w, h);
    gtk_widget_set_name(temp, id);

    this->widget = temp;
  }

  public: const char* getText()
  {
    GtkTextBuffer* buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(this->widget));
    GtkTextIter start;
    gtk_text_buffer_get_iter_at_offset(buffer, &start, 0);
    GtkTextIter end;
    gtk_text_buffer_get_iter_at_offset(buffer, &end, -1);

    const char* temp = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    return temp;
  }

  public: void setText(const char* text)
  {
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(this->widget));
    gtk_text_buffer_set_text(buffer, text, -1);
  }

  public: void reset()
  {
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(this->widget));
    gtk_text_buffer_set_text(buffer, "0", -1);
  }

  public: ~EntryWidget()
  {
    gtk_widget_destroy(this->widget);
  }

};
#endif
