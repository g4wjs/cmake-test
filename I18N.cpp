// ----------------------------------------------------------------------------
// "THE BEER-WARE LICENSE" (Revision 42):
//
// <g4wjs@classdesign.com> modified this file from the original by
// Poul-Henning Kamp <phk@FreeBSD.ORG>. As long as you retain this
// notice you can do whatever you want with this stuff. If we meet
// some day, and you think this stuff is worth it, you can buy me a
// beer in return Bill Somerville.
// ----------------------------------------------------------------------------

#include "I18N.hpp"

#include <QDebug>
#include <QString>
#include <QTranslator>
#include <QLibraryInfo>
#include <QLocale>
#include <QCoreApplication>

#include "pimpl_impl.hpp"

#include "config.h"

class I18N::impl final
{
 public:
  impl (QString const& translations_path, QString const& encoding);
  
 private:
  QTranslator qt_translator_;
  QTranslator default_translator_;
};

I18N::I18N (QString const& translations_path, QString const& encoding)
: m_ {translations_path, encoding}
{
}

I18N::~I18N ()
{
}

I18N::impl::impl (QString const& translations_path, QString const& /* encoding */)
{
  // QTextCodec::setCodecForCStrings (QTextCodec::codecForName (encoding.toLatin1 ()));
  // QTextCodec::setCodecForTr (QTextCodec::codecForName (encoding.toLatin1 ()));

  // set up i18n
  auto locale = QLocale::system ();
  if (qt_translator_.load (locale, "qt", "_", QLibraryInfo::location (QLibraryInfo::TranslationsPath)))
    {
      QCoreApplication::installTranslator (&qt_translator_);
    }
  else
    {
      qDebug () << "failed to load Qt translations for user locale";
    }

  if (default_translator_.load (locale, "cmake-test", "_", translations_path))
    {
      QCoreApplication::installTranslator (&default_translator_);
    }
  else
    {
      qDebug () << "failed to load translations for user locale";
    }
}
