/*
Name: QtRptDesigner
Version: 1.4.5
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net012-2014
*/

#ifndef REPSCROLLAREA_H
#define REPSCROLLAREA_H

#include <QScrollArea>
#include "PageSettingDlg.h"
#include "ReportBand.h"
#include "overlay.h"

namespace Ui {
    class RepScrollArea;
}

int compareBandType(ReportBand *p1, ReportBand *p2);

class RepScrollArea : public QScrollArea
{
    Q_OBJECT
    
public:
    explicit RepScrollArea(QWidget *parent = 0);
    QWidget *repWidget;
    ~RepScrollArea();
    double setPaperSize(qreal scale);
    void paintGrid();
    bool isShowGrid;
    ReportBand *m_addBand(QString bandName, BandType type, QMenu *bandMenu, int m_height=0);
    PageSetting pageSetting;
    void correctBandGeom(QWidget *rep = 0);
    bool allowField();
    void clearReport();
    QWidgetList getReportItems();
    QTreeWidgetItem *rootItem;
    QIcon icon;
    qreal getScale();
    Overlay *overlay;

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::RepScrollArea *ui;
    void paintHorRuler();
    void paintVerRuler();
    QWidget *m_mainWindow;
    double koef;
    qreal m_scale;
    void getKoef();    

public slots:
    void showGrid(bool value);

private slots:
    void bandResing(QRect rect);

signals:
    void bandResing(int);

};

#endif // REPSCROLLAREA_H
