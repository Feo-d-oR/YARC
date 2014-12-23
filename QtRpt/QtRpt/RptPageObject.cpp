/*
Name: QtRpt
Version: 1.4.5
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net
2012-2014
*/

#include "RptPageObject.h"

RptPageObject::RptPageObject() {
    this->orientation=0;
    this->ph=1188;
    this->pw=840;
    this->ml=40;
    this->mr=40;
    this->mt=40;
    this->mb=40;
}

void RptPageObject::setProperty(QtRPT *qtrpt, QDomElement docElem) {
    ph = docElem.attribute("pageHeight").toInt();
    pw = docElem.attribute("pageWidth").toInt();
    ml = docElem.attribute("marginsLeft").toInt();
    mr = docElem.attribute("marginsRight").toInt();
    mt = docElem.attribute("marginsTop").toInt();
    mb = docElem.attribute("marginsBottom").toInt();
    orientation = docElem.attribute("orientation").toInt();
    pageNo = docElem.attribute("pageNo").toInt();
    //---
    QDomNode n = docElem.firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement();
        if ((!e.isNull()) && (e.tagName() == "ReportBand")) {
            RptBandObject *bandObject = new RptBandObject();
            bandObject->parentReportPage = this;
            bandObject->setProperty(qtrpt,e);
            bandList.append(bandObject);
        }
        n = n.nextSibling();
    }
}

void RptPageObject::addBand(RptBandObject *band) {
    band->parentReportPage = this;
    bandList.append(band);
}

RptBandObject *RptPageObject::getBand(BandType type) {
    RptBandObject *result = 0;
    for (int i=0; i<bandList.size(); i++)
        if (bandList.at(i)->type == type)
            result = bandList.at(i);
    return result;
}

RptFieldObject *RptPageObject::findFieldObjectByName(QString name) {
    for (int i=0; i<bandList.size(); i++)
        for (int j=0; j<bandList.at(i)->fieldList.size(); j++)
            if (bandList.at(i)->fieldList.at(j)->name == name)
                return bandList.at(i)->fieldList.at(j);
    return 0;
}

RptPageObject::~RptPageObject() {
    for (int i=0; i<bandList.size(); i++)
        delete bandList.at(i);
    bandList.clear();
}

QDebug operator<<(QDebug dbg, const RptPageObject &obj) {
    dbg << "Report #" << obj.pageNo  << obj.bandList;
    return dbg;
}
