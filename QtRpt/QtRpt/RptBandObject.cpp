/*
Name: QtRpt
Version: 1.4.5
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net
2012-2014
*/

#include "RptBandObject.h"

void RptBandObject::setProperty(QtRPT *qtrpt, QDomElement docElem) {
    name = docElem.attribute("name");
    realHeight = docElem.attribute("height").toInt();
    height = docElem.attribute("height").toInt();
    width = docElem.attribute("width").toInt();
    left = docElem.attribute("left").toInt();
    right = docElem.attribute("right").toInt();
    groupingField = docElem.attribute("groupingField");
    showInGroup = docElem.attribute("showInGroup","0").toInt();
    startNewPage = docElem.attribute("startNewPage","0").toInt();

    if (docElem.attribute("type") == "ReportTitle")
        type = ReportTitle;
    if (docElem.attribute("type") == "PageHeader")
        type = PageHeader;
    if (docElem.attribute("type") == "MasterData")
        type = MasterData;
    if (docElem.attribute("type") == "PageFooter")
        type = PageFooter;
    if (docElem.attribute("type") == "ReportSummary")
        type = ReportSummary;
    if (docElem.attribute("type") == "MasterFooter")
        type = MasterFooter;
    if (docElem.attribute("type") == "MasterHeader")
        type = MasterHeader;
    if (docElem.attribute("type") == "DataGroupHeader")
        type = DataGroupHeader;
    if (docElem.attribute("type") == "DataGroupFooter")
        type = DataGroupFooter;
    //---
    QDomNode n = docElem.firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement();
        RptFieldObject *fieldObject = new RptFieldObject();
        fieldObject->parentBand = this;
        fieldObject->setProperty(qtrpt,e);
        fieldList.append(fieldObject);

        n = n.nextSibling();
    }
}

void RptBandObject::addField(RptFieldObject *field) {
    field->parentBand = this;
    fieldList.append(field);
}

RptBandObject::~RptBandObject() {
    for (int i=0; i<fieldList.size(); i++)
        delete fieldList.at(i);
    fieldList.clear();
}

QDebug operator<<(QDebug dbg, const RptBandObject &obj) {
    dbg << obj.name << obj.fieldList;
    return dbg;
}
