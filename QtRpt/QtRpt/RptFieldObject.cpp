/*
Name: QtRpt
Version: 1.4.5
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net
2012-2014
*/

#include "RptFieldObject.h"

RptFieldObject::RptFieldObject() {
    this->highlighting = "";
    this->backgroundColor = Qt::white;
    this->m_backgroundColor = Qt::white;
    this->fontColor = Qt::black;
    this->m_fontColor = Qt::black;
    QFont font;
    font.setFamily(font.defaultFamily());
    font.setPointSize(12);
    this->font = font;
    this->printing = "1";
    this->borderWidth = 1;
    this->borderColor = Qt::black;
    this->borderBottom = Qt::black;
    this->borderRight = Qt::black;
    this->borderLeft = Qt::black;
    this->borderTop = Qt::black;
    this->aligment = Qt::AlignVCenter | Qt::AlignLeft;
}

void RptFieldObject::setDefaultFontColor(QColor value) {
    fontColor = value;
    m_fontColor = value;
}

void RptFieldObject::setDefaultBackgroundColor(QColor value) {
    backgroundColor = value;
    m_backgroundColor = value;
}

void RptFieldObject::setProperty(QtRPT *qtrpt, QDomElement e) {
    m_qtrpt = qtrpt;
    highlighting = e.attribute("highlighting","");
    printing = e.attribute("printing","1");
    name = e.attribute("name");
    value = e.attribute("value");
    rect.setX(e.attribute("left").toInt());
    rect.setY(e.attribute("top").toInt());
    rect.setWidth((e.attribute("width").toInt()));
    rect.setHeight(e.attribute("height").toInt());
    borderTop = colorFromString(e.attribute("borderTop"));
    borderBottom = colorFromString(e.attribute("borderBottom"));
    borderLeft = colorFromString(e.attribute("borderLeft"));
    borderRight = colorFromString(e.attribute("borderRight"));
    borderWidth = e.attribute("borderWidth","1").replace("px","").toInt();
    borderStyle = e.attribute("borderStyle","solid");
    borderColor = colorFromString(e.attribute("borderColor"));

    aligment = QtRPT::getAligment(e);
    autoHeight = e.attribute("autoHeight","0").toInt();

    QFont m_font(e.attribute("fontFamily"),e.attribute("fontSize").toInt());
    m_font.setBold(e.attribute("fontBold").toInt());
    m_font.setItalic(e.attribute("fontItalic").toInt());
    m_font.setUnderline(e.attribute("fontUnderline").toInt());
    m_font.setStrikeOut(e.attribute("fontStrikeout").toInt());
    font = m_font;

    backgroundColor = colorFromString(e.attribute("backgroundColor"));
    m_backgroundColor = backgroundColor;
    fontColor = colorFromString(e.attribute("fontColor"));
    m_fontColor = fontColor;

    imgFormat = e.attribute("imgFormat","PNG");
    textWrap = e.attribute("textWrap","1").toInt();

    fieldType = qtrpt->getFieldType(e);
    formatString = e.attribute("format","");

    barcodeType = e.attribute("barcodeType","13").toInt();
    barcodeFrameType = e.attribute("barcodeFrameType","0").toInt();

    picture = QByteArray::fromBase64(e.attribute("picture","text").toLatin1());
    ignoreAspectRatio = e.attribute("ignoreAspectRatio","1").toInt();

    showGrid = e.attribute("showGrid","1").toInt();
    showLegend = e.attribute("showLegend","1").toInt();
    showCaption = e.attribute("showCaption","1").toInt();
    showGraphCaption = e.attribute("showGraphCaption","1").toInt();
    showPercent = e.attribute("showPercent","1").toInt();
    caption = e.attribute("caption","Example");
    autoFillData = e.attribute("autoFillData","0").toInt();

    lineStartX = e.attribute("lineStartX").toInt();
    lineEndX = e.attribute("lineEndX").toInt();
    lineStartY = e.attribute("lineStartY").toInt();
    lineEndY = e.attribute("lineEndY").toInt();
    arrowStart = e.attribute("arrowStart","0").toInt();
    arrowEnd = e.attribute("arrowEnd","0").toInt();

    if (fieldType == Diagram) {
        if (autoFillData == 1) {
            QDomNode g = e.firstChild();
            while(!g.isNull()) {
                QDomElement ge = g.toElement(); // try to convert the node to an element.

                GraphParam param;
                param.color = colorFromString( ge.attribute("color") );
                param.valueReal = qtrpt->sectionField(this->parentBand, ge.attribute("value"), false).toFloat();
                param.formula = ge.attribute("value");
                param.caption = ge.attribute("caption");
                graphList.append(param);

                g = g.nextSibling();
            }
        }
    }
}

void RptFieldObject::updateHighlightingParam() {
    QFont m_font(font);
    m_font.setBold(m_qtrpt->processHighligthing(this, FntBold).toInt());
    m_font.setItalic(m_qtrpt->processHighligthing(this, FntItalic).toInt());
    m_font.setUnderline(m_qtrpt->processHighligthing(this, FntUnderline).toInt());
    m_font.setStrikeOut(m_qtrpt->processHighligthing(this, FntStrikeout).toInt());
    font = m_font;

    backgroundColor = colorFromString(m_qtrpt->processHighligthing(this, BgColor).toString());
    fontColor = colorFromString(m_qtrpt->processHighligthing(this, FntColor).toString());
}

void RptFieldObject::updateDiagramValue() {
    if (autoFillData == 1) {
        for (int h=0; h<graphList.size(); h++) {
            graphList[h].valueReal = m_qtrpt->sectionField(this->parentBand, graphList.at(h).formula, false).toFloat();
        }
    }
}

QDebug operator<<(QDebug dbg, const RptFieldObject &obj) {
    dbg << obj.name;
    return dbg;
}

