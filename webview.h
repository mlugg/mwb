#pragma once

#include <gtkmm/widget.h>
#include <webkit2/webkit2.h>

class GtkWebView : public Gtk::Widget {
public:
  GtkWebView() : Gtk::Widget((webkit_web_view_new())) {}
  
  operator WebKitWebView *() {
    return WEBKIT_WEB_VIEW(gobj());
  }

  void loadUri(const gchar *strUri) {
    webkit_web_view_load_uri(*this, strUri);
  }
};
