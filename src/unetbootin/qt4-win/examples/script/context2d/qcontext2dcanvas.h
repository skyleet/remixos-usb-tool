/****************************************************************************
**
** Copyright (C) 1992-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License versions 2.0 or 3.0 as published by the Free Software
** Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file.  Alternatively you may (at
** your option) use any later version of the GNU General Public
** License if such license has been publicly approved by Trolltech ASA
** (or its successors, if any) and the KDE Free Qt Foundation. In
** addition, as a special exception, Trolltech gives you certain
** additional rights. These rights are described in the Trolltech GPL
** Exception version 1.2, which can be found at
** http://www.trolltech.com/products/qt/gplexception/ and in the file
** GPL_EXCEPTION.txt in this package.
**
** Please review the following information to ensure GNU General
** Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/. If
** you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech, as the sole
** copyright holder for Qt Designer, grants users of the Qt/Eclipse
** Integration plug-in the right for the Qt/Eclipse Integration to
** link to functionality provided by Qt Designer and its related
** libraries.
**
** This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
** INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE. Trolltech reserves all rights not expressly
** granted herein.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef QCONTEXT2DCANVAS_H
#define QCONTEXT2DCANVAS_H

#include <qscriptengine.h>
#include <qscriptcontext.h>
#include <qscriptvalue.h>

#include <QWidget>
#include <QTimer>

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QMouseEvent;
QT_END_NAMESPACE
class Context2D;

class QContext2DCanvas : public QWidget
{
    Q_OBJECT
public:
    QContext2DCanvas(QWidget *parent=0);
    ~QContext2DCanvas();

    QScriptEngine *engine();

public slots:
    void setScriptContents(const QString &txt);
    QObject *getContext(const QString &str) const;
    void setInterval(const QScriptValue &func,
                     qreal interval);
    void resize(int w, int h);
signals:
    void error(const QString &error, int lineno);
protected:
    virtual void paintEvent(QPaintEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);
    virtual void resizeEvent(QResizeEvent *e);

private:
    QScriptEngine      m_engine;
    QString            m_script;

    Context2D         *m_context;
    QScriptValue       m_self;
    QScriptValue       m_doc;

    QScriptValue       m_intervalFunc;
    QTimer             m_timer;

    bool               m_firstRun;

    QScriptValue       m_keyDownHandler;
    QScriptValue       m_keyUpHandler;
    QScriptValue       m_mouseDownHandler;
    QScriptValue       m_mouseUpHandler;
    QScriptValue       m_mouseMoveHandler;
};

#endif