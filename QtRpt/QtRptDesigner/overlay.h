/*
Name: QtRptDesigner
Version: 1.4.5
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net
2012-2014
*/

#ifndef OVERLAY_H
#define OVERLAY_H

#include <QWidget>
#include <QPainter>
#include <QPoint>
#include "RptContainer.h"

typedef QList<RptContainer *> ContList;

class Overlay : public QWidget
{
    Q_OBJECT
public:
    Overlay(QWidget *parent);    
    QWidget *ww;

private:
    ContList allContList;

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // OVERLAY_H
