// ----------------------------------------------------------------------------
// "THE BEER-WARE LICENSE" (Revision 42):
//
// <g4wjs@classdesign.com> modified this file from the original by
// Poul-Henning Kamp <phk@FreeBSD.ORG>. As long as you retain this
// notice you can do whatever you want with this stuff. If we meet
// some day, and you think this stuff is worth it, you can buy me a
// beer in return Bill Somerville.
// ----------------------------------------------------------------------------

#include "MainWindow.hpp"

#include <memory>

#include <QObject>
#include <QMainWindow>
#include <QSettings>

#include "pimpl_impl.hpp"

#include "ui_MainWindow.h"

class MainWindow::impl final
  : public QMainWindow
{
  Q_OBJECT;

 private:
  Q_DISABLE_COPY (impl);

 public:
  explicit impl (MainWindow *);

 private:
  void read_settings ();
  void write_settings () const;

  Q_SLOT void closeEvent (QCloseEvent * e) override;

  MainWindow * self_;		// back pointer
  std::unique_ptr<Ui::MainWindow> ui_;
};

#include "MainWindow.moc"

MainWindow::MainWindow ()
  : m_ {this}
{
}

MainWindow::~MainWindow ()
{
}

MainWindow::impl::impl (MainWindow * self)
  : QMainWindow {}
  , self_ {self}
  , ui_ {new Ui::MainWindow}
{
  ui_->setupUi (this);
  read_settings ();
  show ();
}

void MainWindow::impl::closeEvent (QCloseEvent * e)
{
  write_settings ();
  QMainWindow::closeEvent (e);
}

void MainWindow::impl::read_settings ()
{
  QSettings settings;
  settings.beginGroup ("MainWindow");
  resize (settings.value ("window/size", size ()).toSize ());
  move (settings.value ("window/pos", pos ()).toPoint ());
  restoreState (settings.value ("window/state", saveState ()).toByteArray ());
  settings.endGroup ();
}

void MainWindow::impl::write_settings () const
{
  QSettings settings;
  settings.beginGroup ("MainWindow");
  settings.setValue ("window/size", size ());
  settings.setValue ("window/pos", pos ());
  settings.setValue ("window/state", saveState ());
  settings.endGroup ();
}
