#include <stdexcept>
#include <gtkmm/cssprovider.h>
#include "main_window.h"

MwbWindow::MwbWindow() : rootBox(Gtk::ORIENTATION_VERTICAL), btnBack("<-"), btnForward("->"), btnReload("Reload"), btnNewTab("+") {
  auto file = Gio::File::create_for_path("style.css");
  auto css = Gtk::CssProvider::create();
  if (!css->load_from_file(file))
    throw std::runtime_error("Failed to load style CSS!");

  auto screen = Gdk::Screen::get_default();
  auto ctx = get_style_context();
  ctx->add_provider_for_screen(screen, css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  set_title("mwb");
  set_border_width(1);

  add(rootBox);

  rootBox.pack_start(titleBox, Gtk::PACK_SHRINK);
  rootBox.pack_start(notebook);

  GtkWebView *webView = new GtkWebView();
  notebook.append_page(*webView, "Google");

  webView->loadUri("https://google.com");

  titleBox.pack_start(btnBack, Gtk::PACK_SHRINK);
  titleBox.pack_start(btnForward, Gtk::PACK_SHRINK);
  titleBox.pack_start(btnReload, Gtk::PACK_SHRINK);
  titleBox.pack_start(addressBar);
  titleBox.pack_start(btnNewTab, Gtk::PACK_SHRINK);

  btnBack.signal_clicked().connect(sigc::mem_fun(*this, &MwbWindow::back));
  btnForward.signal_clicked().connect(sigc::mem_fun(*this, &MwbWindow::forward));
  btnReload.signal_clicked().connect(sigc::mem_fun(*this, &MwbWindow::reload));
  notebook.signal_switch_page().connect(sigc::mem_fun(*this, &MwbWindow::onSwitchTab));
  addressBar.signal_activate().connect(sigc::mem_fun(*this, &MwbWindow::goUri));
  btnNewTab.signal_clicked().connect(sigc::mem_fun(*this, &MwbWindow::newTab));

  show_all_children();
}

void MwbWindow::back() {
  GtkWebView *wv = reinterpret_cast<GtkWebView *>(notebook.get_nth_page(notebook.get_current_page()));
  webkit_web_view_go_back(*wv);
}

void MwbWindow::forward() {
  GtkWebView *wv = reinterpret_cast<GtkWebView *>(notebook.get_nth_page(notebook.get_current_page()));
  webkit_web_view_go_forward(*wv);
}

void MwbWindow::reload() {
  GtkWebView *wv = reinterpret_cast<GtkWebView *>(notebook.get_nth_page(notebook.get_current_page()));
  webkit_web_view_reload(*wv);
}

void MwbWindow::onSwitchTab(Gtk::Widget *page, guint page_num) {
  GtkWebView *wv = reinterpret_cast<GtkWebView *>(page);
  addressBar.set_text(webkit_web_view_get_uri(*wv));
}

void MwbWindow::goUri() {
  GtkWebView *wv = reinterpret_cast<GtkWebView *>(notebook.get_nth_page(notebook.get_current_page()));
  wv->loadUri(addressBar.get_text().c_str());
}

void MwbWindow::newTab() {
  GtkWebView *wv = new GtkWebView();
  notebook.append_page(*wv, "Tab");
  wv->loadUri("https://google.com");
  wv->show();
}

