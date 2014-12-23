/*
Name: QtRptDesigner
Version: 1.4.5
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net012-2014
*/

#ifndef REPORTBAND_H
#define REPORTBAND_H

#include <QWidget>
#include <QObject>
#include <QMouseEvent>
#include <QTreeWidgetItem>
#include <qlabelex.h>
#include "TContainerField.h"
#include "TContainerLine.h"

namespace Ui {
    class ReportBand;
}

class ReportBand : public QWidget
{
    Q_OBJECT
    
public:
    BandType bandType;
    int titleHeight;
    QTreeWidgetItem *itemInTree;
    explicit ReportBand(QWidget *parent = 0, BandType type = ReportTitle, QTreeWidgetItem *item = 0);

    QWidget *contWidget;
    TContainerLine *newContLine;
    void newFeildTreeItem(QObject *widget);
    void setMenu(QMenu *menu_);
    qreal scale;
    void setTitleHeight(int h);
    QString getGroupingField();
    void setGroupingField(QString value);
    int getStartNewNumertaion();
    void setStartNewNumeration(bool value);
    bool getShowInGroup();
    void setShowInGroup(bool value);
    bool getStartNewPage();
    void setStartNewPage(bool value);
    ~ReportBand();

private:
    int mode;
    bool m_infocus;
    void setCursorShape(const QPoint &e_pos);
    QString m_groupingField;
    bool m_startNewNumeration;
    bool m_showInGroup;
    bool m_startNewPage;
    Ui::ReportBand *ui;

signals:
    void inFocus(bool mode);
    void endResizing(QRect rect);
    void delBand(QTreeWidgetItem *);

protected:
    QPoint position;
    QPointF mousePos;
    bool eventFilter( QObject *obj, QEvent *evt );
    void resizeEvent (QResizeEvent *event);
    void focusInEvent(QFocusEvent *);
    void focusOutEvent(QFocusEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
};

#endif // REPORTBAND_H
