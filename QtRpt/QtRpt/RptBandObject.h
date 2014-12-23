/*
Name: QtRpt
Version: 1.4.5
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net
2012-2014
*/

#ifndef RPTBANDOBJECT_H
#define RPTBANDOBJECT_H

#include <RptFieldObject.h>

using namespace QtRptName;

class QtRPT;
class RptPageObject;
class RptFieldObject;

class RptBandObject
{
    friend class QtRPT;
    friend class RptPageObject;
public:
    RptBandObject() {}
    ~RptBandObject();
    QString name;
    QString groupingField;
    int showInGroup;
    int startNewPage;
    int startNewNumeration;
    int realHeight;
    int height;
    int width;
    int left;
    int right;
    BandType type;
    void addField(RptFieldObject *field);
    QList<RptFieldObject*> fieldList;
    RptPageObject *parentReportPage;

private:
    void setProperty(QtRPT *qtrpt, QDomElement docElem);
};
Q_DECLARE_METATYPE(RptBandObject)
QDebug operator<<(QDebug dbg, const RptBandObject &obj);


#endif // RPTBANDOBJECT_H
