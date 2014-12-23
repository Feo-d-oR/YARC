/*
Name: QtRptDesigner
Version: 1.4.5
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net
2012-2014
*/

#include "overlay.h"

Overlay::Overlay(QWidget *parent) : QWidget(parent) {
    setPalette(Qt::transparent);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    allContList = ContList();
}

void Overlay::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    //painter.setPen(QColor("blue"));
    //painter.drawLine(QPoint(0,0),QPoint(this->width(),this->height()));

    allContList = ContList();
    allContList << this->parentWidget()->findChildren<RptContainer *>();

    for (int i=0; i<allContList.size(); i++) {
        if (allContList.at(i)->isSelected() && allContList.at(i)->isAllowDrawSelection()) {
            RptContainer *w = qobject_cast<RptContainer *>(allContList.at(i));
            if (w == 0) return;
            if (w == NULL) return;

            QPoint pc = allContList.at(i)->mapToParent(QPoint(-3,-3));
            QPoint pb = allContList.at(i)->parentWidget()->mapToParent(pc);
            QPoint LT = allContList.at(i)->parentWidget()->parentWidget()->mapToParent(pb);

            QPoint LB = QPoint(LT.x(),LT.y()+w->height());
            QPoint RB = QPoint(LT.x()+w->width(),LT.y()+w->height());
            QPoint CB = QPoint(LT.x()+w->width()/2,LT.y()+w->height());
            QPoint RT = QPoint(LT.x()+w->width(),LT.y());
            QPoint CT = QPoint(LT.x()+w->width()/2,LT.y());

            painter.fillRect(LT.x(),LT.y(),6,6,QColor("blue"));
            painter.fillRect(LB.x(),LB.y(),6,6,QColor("blue"));
            painter.fillRect(RB.x(),RB.y(),6,6,QColor("blue"));
            painter.fillRect(CB.x(),CB.y(),6,6,QColor("blue"));
            painter.fillRect(RT.x(),RT.y(),6,6,QColor("blue"));
            painter.fillRect(CT.x(),CT.y(),6,6,QColor("blue"));
        }
    }
}
