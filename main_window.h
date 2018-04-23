#pragma once

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/notebook.h>
#include <gtkmm/entry.h>
#include "webview.h"

class MwbWindow : public Gtk::Window
{
public:
  MwbWindow();

protected:
  Gtk::Box rootBox;
  Gtk::Box titleBox;
  Gtk::Notebook notebook;
  Gtk::Button btnBack, btnForward, btnReload, btnNewTab;
  Gtk::Entry addressBar;

  void back();
  void forward();
  void reload();
  void onSwitchTab(Gtk::Widget* page, guint page_num);
  void goUri();
  void newTab();
};
