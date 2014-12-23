/*
Name: QtRpt
Version: 1.4.5
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net
2012-2014
*/

#ifndef RPTFIELDOBJECT_H
#define RPTFIELDOBJECT_H

#include <QDomDocument>
#include "qtrpt.h"
#include <qtrptnamespace.h>

using namespace QtRptName;

class QtRPT;
class RptBandObject;

class RptFieldObject
{
    friend class QtRPT;
    friend class RptBandObject;
public:
    RptFieldObject();
    QString name;
    QString value;
    QRect rect;
    QColor borderTop;
    QColor borderBottom;
    QColor borderLeft;
    QColor borderRight;
    QColor borderColor;

    QColor fontColor;
    QColor backgroundColor;

    void setDefaultFontColor(QColor value);
    void setDefaultBackgroundColor(QColor value);

    int borderWidth;
    int autoHeight;
    int textWrap;

    Qt::Alignment aligment;
    QString borderStyle;
    QFont font;
    FieldType fieldType;
    QString formatString;
    QString highlighting;
    QString imgFormat;
    QString printing;
    int barcodeType;
    int barcodeFrameType;
    int ignoreAspectRatio;
    QByteArray picture;
    RptBandObject *parentBand;

    int lineStartX;
    int lineEndX;
    int lineStartY;
    int lineEndY;
    int arrowStart;
    int arrowEnd;

    int showGrid;
    int showLegend;
    int showCaption;
    int showGraphCaption;
    int showPercent;
    int autoFillData;
    QString caption;
    QList<GraphParam> graphList;

    int recNo() {return m_recNo;}
    int reportPage() {return m_reportPage;}

private:

    QColor m_fontColor;
    QColor m_backgroundColor;
    int m_recNo;
    int m_reportPage;
    QtRPT *m_qtrpt;
    void setProperty(QtRPT *qtrpt, QDomElement e);
    void updateDiagramValue();
    void updateHighlightingParam();
};
Q_DECLARE_METATYPE(RptFieldObject)
QDebug operator<<(QDebug dbg, const RptFieldObject &obj);

#endif // RPTFIELDOBJECT_H
