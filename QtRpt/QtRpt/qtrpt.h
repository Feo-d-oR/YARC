/*
Name: QtRpt
Version: 1.4.5
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net
2012-2014
*/

#ifndef QTRPT_H
#define QTRPT_H

class QWidget;
#include <QPainter>
#include <QDomDocument>
#include <QScriptEngine>
#include <QPrintPreviewWidget>
#include <QtScript>
#include <QPrintDialog>
#include <QDesktopServices>
#include <CommonClasses.h>
#include <qtrptnamespace.h>
#include <chart.h>
#include "RptSql.h"
#include <Barcode.h>
#include <RptFieldObject.h>
#include <RptBandObject.h>
#include <RptPageObject.h>

using namespace QtRptName;

enum HiType {
    FntBold,
    FntItalic,
    FntUnderline,
    FntStrikeout,
    FntColor,
    BgColor
};

struct AggregateValues {
    QString paramName;
    QVariant paramValue;
    int lnNo;
    int pageReport;
};

class RptPageObject;
class RptBandObject;
class RptFieldObject;

QScriptValue funcAggregate(QScriptContext *context, QScriptEngine *engine);
static QList<AggregateValues> listOfPair;
static QList<int> listIdxOfGroup;

class QtRPT : public QWidget
{
    Q_OBJECT
    friend class RptFieldObject;
    friend class RptBandObject;
public:
    QList<int> recordCount;
    explicit QtRPT(QWidget *parent = 0);    
    bool loadReport(QString fileName);
    bool loadReport(QDomDocument xmlDoc);
    void clearObject();
    void printExec(bool maximum = false, bool direct = false, QString printerName = QString());
    //void setCallbackFunc(void (*func)(int &recNo, QString &paramName, QVariant &paramValue));
    void setBackgroundImage(QPixmap image);
    void printPDF(const QString &filePath, bool open = true);    
    static FieldType getFieldType(QDomElement e);
    static QString getFieldTypeName(FieldType type);
    static QList<FieldType> getDrawingFields();
    static Qt::PenStyle getPenStyle(QString value);
    QList<RptPageObject*> pageList;
    ~QtRPT();

private:    
    QPixmap *m_backgroundImage;
    QPainter painter;
    int m_recNo;
    int mg_recNo;
    int m_pageReport;
    float koefRes_h;
    float koefRes_w;
    int ph;
    int pw;
    int ml;
    int mr;
    int mt;
    int mb;
    int curPage;
    int totalPage;
    int m_orientation;
    QPrintPreviewWidget *pr;
    QList<QAction *> lst ;
    QDomDocument *xmlDoc;
    QDomNode getBand(BandType type, QDomElement docElem);
    void drawBandRow(RptBandObject *band, int bandTop, bool allowDraw = true);
    void fillListOfValue(RptBandObject *bandObject);
    QString sectionField(RptBandObject *band, QString value, bool exp, bool firstPass = false, QString formatString = "");
    QStringList splitValue(QString value);
    QImage sectionFieldImage(QString value);
    QVariant processFunctions(QString value);
    QString sectionValue(QString paramName);
    QImage sectionValueImage(QString paramName);
    void newPage(QPrinter *printer, int &y, bool draw, bool newReportPage = false);
    void processPHeader(int &y, bool draw);
    void processPFooter(bool draw);
    void processMFooter(QPrinter *printer, int &y, bool draw);
    void processRSummary(QPrinter *printer, int &y, bool draw);
    //void (*callbackFunc)(int &recNo, QString &paramName, QVariant &paramValue);
    void processReport(QPrinter *printer, bool draw, int pageReport);
    void processRTitle(int &y, bool draw);
    void processMHeader(int &y, bool draw);
    void processMasterData(QPrinter *printer, int &y, bool draw, int pageReport);
    void prcessGroupHeader(QPrinter *printer, int &y, bool draw, int pageReport);
    void setPageSettings(QPrinter *printer, int pageReport);
    void drawBackground(QPainter &painter);
    bool isFieldVisible(RptFieldObject *fieldObject);
    QVariant processHighligthing(RptFieldObject *field, HiType type);
    bool allowPrintPage(bool draw, int curPage_);
    bool allowNewPage(bool draw, int curPage_);
    int fromPage;
    int toPage;
    QStringList listOfGroup;
    QString getFormattedValue(QString value, QString formatString);
    void setFont(RptFieldObject *fieldObject);
    static Qt::Alignment getAligment(QDomElement e);
    QPen getPen(RptFieldObject *fieldObject);
    void drawFields(RptFieldObject *fieldObject, int bandTop, bool firstPass);
    void drawLines(RptFieldObject *fieldObject, int bandTop);
    void openDataSource(int pageReport);
    RptSql *rptSql;
    void makeReportObjectStructure();    

protected:
    bool eventFilter(QObject *obj, QEvent *e);

signals:
    void setValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage);
    void setField(RptFieldObject &fieldObject);
    void setValueImage(int &recNo, QString &paramName, QImage &paramValue, int reportPage);
    void setValueDiagram(Chart &chart);

public slots:
    void printPreview(QPrinter *printer);

};

#endif // QTRPT_H
