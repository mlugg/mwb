#include <gtkmm/application.h>
#include "main_window.h"

int main(int argc, char *argv[]) {
  auto app = Gtk::Application::create(argc, argv, "co.uk.mlugg.mwb");

  MwbWindow mwb;

  return app->run(mwb);
}

