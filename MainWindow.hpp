#ifndef MAIN_WINDOW_HPP__
#define MAIN_WINDOW_HPP__

// ----------------------------------------------------------------------------
// "THE BEER-WARE LICENSE" (Revision 42):
//
// <g4wjs@classdesign.com> modified this file from the original by
// Poul-Henning Kamp <phk@FreeBSD.ORG>. As long as you retain this
// notice you can do whatever you want with this stuff. If we meet
// some day, and you think this stuff is worth it, you can buy me a
// beer in return Bill Somerville.
// ----------------------------------------------------------------------------

#include "pimpl_h.hpp"

class MainWindow final
{
public:
  MainWindow ();
  ~MainWindow ();

private:
  class impl;
  pimpl<impl> m_;
};

#endif
