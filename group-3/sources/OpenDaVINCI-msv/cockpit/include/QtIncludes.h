/*
 * OpenDaVINCI.
 *
 * This software is open source. Please see COPYING and AUTHORS for further information.
 */

#ifndef COCKPIT_QTINCLUDES_H_
#define COCKPIT_QTINCLUDES_H_

#ifdef PANDABOARD
#include <stdc-predef.h>
#endif

#if defined __GNUC__
#pragma GCC system_header
#elif defined __SUNPRO_CC
#pragma disable_warn
#elif defined _MSC_VER
#pragma warning(push, 1)
#endif

#include <Qt/qaction.h>
#include <Qt/qapplication.h>
#include <Qt/qcheckbox.h>
#include <Qt/qcombobox.h>
#include <Qt/qdesktopwidget.h>
#include <Qt/qdial.h>
#include <Qt/qevent.h>
#include <Qt/qfile.h>
#include <Qt/qfiledialog.h>
#include <Qt/qfont.h>
#include <Qt/qframe.h>
#include <Qt/qgridlayout.h>
#include <Qt/qgroupbox.h>
#include <Qt/qicon.h>
#include <Qt/qimage.h>
#include <Qt/qmdiarea.h>
#include <Qt/qmdisubwindow.h>
#include <Qt/qmenu.h>
#include <Qt/qmenubar.h>
#include <Qt/qmessagebox.h>
#include <Qt/qlabel.h>
#include <Qt/qlocale.h>
#include <Qt/qlistwidget.h>
#include <Qt/qpainter.h>
#include <Qt/qprogressbar.h>
#include <Qt/qpushbutton.h>
#include <Qt/qscrollarea.h>
#include <Qt/qslider.h>
#include <Qt/qspinbox.h>
#include <Qt/qstandarditemmodel.h>
#include <Qt/qstring.h>
#include <Qt/qstringlist.h>
#include <Qt/qtabwidget.h>
#include <Qt/qtextedit.h>
#include <Qt/qtextstream.h>
#include <Qt/qtimer.h>
#include <Qt/qtranslator.h>
#include <Qt/qtreeview.h>
#include <Qt/qtreewidget.h>
#include <Qt/qurl.h>
#include <Qt/qwidget.h>
#include <Qt/qmainwindow.h>
#include <Qt/qdockwidget.h>
#include <Qt/qinputdialog.h>

#include <QtCore/qtimer.h>
#include <QtCore/qrect.h>
#include <QtCore/qmetatype.h>

#ifndef PANDABOARD
#include <qwt-qt4/qwt_plot.h>
#include <qwt-qt4/qwt_plot_curve.h>
#endif

#if defined __SUNPRO_CC
#pragma enable_warn
#elif defined _MSC_VER
#pragma warning(pop)
#endif

Q_DECLARE_METATYPE(int32_t)

#endif /*COCKPIT_QTINCLUDES_H_*/
