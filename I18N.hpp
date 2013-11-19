// ----------------------------------------------------------------------------
// "THE BEER-WARE LICENSE" (Revision 42):
//
// <g4wjs@classdesign.com> modified this file from the original by
// Poul-Henning Kamp <phk@FreeBSD.ORG>. As long as you retain this
// notice you can do whatever you want with this stuff. If we meet
// some day, and you think this stuff is worth it, you can buy me a
// beer in return Bill Somerville.
// ----------------------------------------------------------------------------

#ifndef I18N_HPP_
#define I18N_HPP_

#include <QString>

#include "pimpl_h.hpp"

#include "config.h"

class I18N final
{
public:
  explicit I18N (QString const& translations_path, QString const& encoding = "UTF-8");
  ~I18N ();

private:
  class impl;
  pimpl<impl> m_;
};

#endif
