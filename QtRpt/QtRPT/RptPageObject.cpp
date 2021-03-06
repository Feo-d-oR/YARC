/*
Name: QtRpt
Version: 2.0.0
Web-site: http://www.qtrpt.tk
Programmer: Aleksey Osipov
E-mail: aliks-os@ukr.net
Web-site: http://www.aliks-os.tk

Copyright 2012-2016 Aleksey Osipov

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "RptPageObject.h"

/*!
 \class RptPageObject
 \inmodule RptPageObject.cpp
 \brief The RptPageObject class allow to construct the QtRPT report from scrutch.
 RptPageObject represent report's page. On RptPageObject the RptBandObjects are placed

  The inner structure of report is following:
  \code
  QtRPT
    RptPageObject
      RptBandObject
        RptFieldObject
  \endcode
  There are possible to have some RptPageObject in the report.
  It allows combining several reports in one Report.
*/

/*!
 \variable RptPageObject::pageNo
 \brief The number of report's page.
*/

/*!
 \variable RptPageObject::orientation
 \brief The orientation of report's page.
*/

/*!
 \variable RptPageObject::ph
 \brief The height of report's page.
*/

/*!
 \variable RptPageObject::pw
 \brief The width of report's page.
*/

/*!
 \variable RptPageObject::ml
 \brief The left's margin of report's page.
*/

/*!
 \variable RptPageObject::mr
 \brief The girht's margin of report's page.
*/

/*!
 \variable RptPageObject::mt
 \brief The top's margin of report's page.
*/

/*!
 \variable RptPageObject::mb
 \brief The buttom's margin of report's page.
*/

/*!
 \variable RptPageObject::border
 \brief Sets draw or not border arround the page. Defualt is false.
*/

/*!
 \variable RptPageObject::borderWidth
 \brief The border's width of report's page. Default value is 1px.
*/

/*!
 \variable RptPageObject::borderColor
 \brief The border's color of report's page. Default is Qt::black
*/

/*!
 \variable RptPageObject::borderStyle
 \brief The border's style of report's page. Default value is "solid"
*/

/*!
 \fn RptPageObject::RptPageObject()
    Constructs a RptPageObject object.
*/
RptPageObject::RptPageObject(QtRPT *qtrpt) {
	this->m_qtrpt = qtrpt;
    this->orientation=0;
    this->ph=1188;
    this->pw=840;
    this->ml=40;
    this->mr=40;
    this->mt=40;
    this->mb=40;
    this->border = false;
    this->borderWidth = 1;
    this->borderColor = Qt::black;
    this->borderStyle = "solid";
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
    border = docElem.attribute("border").toInt();
    borderWidth = docElem.attribute("borderWidth").toInt();
    borderColor = colorFromString(docElem.attribute("borderColor"));
    borderStyle = docElem.attribute("borderStyle");
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

/*!
 \fn void RptPageObject::addBand(RptBandObject *band)
    Add \a band to current RptBandObject object.

    \sa RptBandObject
*/
void RptPageObject::addBand(RptBandObject *band) {
    band->parentReportPage = this;
	band->m_qtrpt = this->m_qtrpt;
    bandList.append(band);
}

/*!
 \fn RptBandObject RptPageObject::getBand(BandType type)
    Find and return \c RptBandObject on this report page the field by
    the given \a type.

    \sa RptBandObject
*/
RptBandObject *RptPageObject::getBand(BandType type) {
    RptBandObject *result = 0;
    for (int i=0; i<bandList.size(); i++)
        if (bandList.at(i)->type == type)
            result = bandList.at(i);
    return result;
}

/*!
 \fn RptFieldObject RptPageObject::findFieldObjectByName(QString name)
    Find and return \c RptFieldObject on this report page the field with
    the given \a name.

    \sa RptFieldObject
*/
RptFieldObject *RptPageObject::findFieldObjectByName(QString name) {
    for (int i=0; i<bandList.size(); i++)
        for (int j=0; j<bandList.at(i)->fieldList.size(); j++)
            if (bandList.at(i)->fieldList.at(j)->name == name)
                return bandList.at(i)->fieldList.at(j);
    return 0;
}

/*!
  Destroys the object, deleting all its child objects.
 */
RptPageObject::~RptPageObject() {
    for (int i=0; i<bandList.size(); i++)
        delete bandList.at(i);
    bandList.clear();
}

QDebug operator<<(QDebug dbg, const RptPageObject &obj) {
    dbg << "Report #" << obj.pageNo  << obj.bandList;
    return dbg;
}
