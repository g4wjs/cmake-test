// ----------------------------------------------------------------------------
// "THE BEER-WARE LICENSE" (Revision 42):
//
// <g4wjs@classdesign.com> modified this file from the original by
// Poul-Henning Kamp <phk@FreeBSD.ORG>. As long as you retain this
// notice you can do whatever you want with this stuff. If we meet
// some day, and you think this stuff is worth it, you can buy me a
// beer in return Bill Somerville.
// ----------------------------------------------------------------------------

#include <iostream>
#include <exception>

#include <locale.h>

#include <QApplication>
#include <QSettings>
#include <QObject>
#include <QTranslator>
#include <QLibraryInfo>
#include <QLocale>

#include "MainWindow.hpp"

int main (int argc, char * argv[])
{
  try
    {
      QApplication application (argc, argv);

      setlocale (LC_NUMERIC, "C"); // ensure number forms are in
				   // consistent format, do this after
				   // instantiating QApplication so
				   // that GUI has correct l18n

      application.setOrganizationName ("Class Design Ltd.");
      application.setOrganizationDomain ("classdesign.com");
      application.setApplicationName ("cmake-test");

      // set up i18n
      QString locale_name {QLocale::system ().name ()};

      QTranslator qt_translator;
      qt_translator.load ("qt_" + locale_name, QLibraryInfo::location (QLibraryInfo::TranslationsPath));
      application.installTranslator (&qt_translator);

      QTranslator translator;
      translator.load ("cmake-test_" + locale_name);
      application.installTranslator (&translator);

      // create main window
      MainWindow main_window;

      // hook up closedown
      QObject::connect (&application, SIGNAL (lastWindowClosed ()), &application, SLOT (quit ()));

      // run the GUI event loop
      return application.exec ();
    }
  catch (std::exception const& e)
    {
      std::cerr << "Error: " << e.what () << '\n';
    }
  catch (...)
    {
      std::cerr << "Unexpected error\n";
      throw;
    }
  return -1;
}
