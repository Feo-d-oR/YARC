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

#include "GraphicsHelperClass.h"
#include "EditFldDlg.h"
#include "GraphicsLine.h"
#include "GraphicsBox.h"
#include "UndoRedoCommands.h"
#include "mainwindow.h"

GraphicsHelperClass::GraphicsHelperClass(QObject *parent) : QObject(parent) {
    m_menu = new QMenu();
    m_printing = "1";
    borderWidth = 1;
    itemInTree = nullptr;
    m_backgroundColor = Qt::white;
    m_borderLeftColor = Qt::black;
    m_borderRightColor = Qt::black;
    m_borderTopColor = Qt::black;
    m_borderBottomColor = Qt::black;
    m_borderStyle = Qt::SolidLine;
    m_borderColor = Qt::black;
}

void GraphicsHelperClass::setObjectName(const QString &name) {
    QObject::setObjectName(name);
    if (itemInTree != nullptr)
        itemInTree->setText(0, name);
}

QColor GraphicsHelperClass::getColorValue(Command param) {
    switch(param) {
        case FontColor: {
            return m_fontColor;
            break;
        }
        case BackgroundColor: {
            return m_backgroundColor;
            break;
        }
        case BorderColor: {
            return m_borderColor;
            break;
        }
        case FrameTop: {
            return m_borderTopColor;
            break;
        }
        case FrameBottom: {
            return m_borderBottomColor;
            break;
        }
        case FrameLeft: {
            return m_borderLeftColor;
            break;
        }
        case FrameRight: {
            return m_borderRightColor;
            break;
        }

        default: return QColor();
    }
}

void GraphicsHelperClass::setColorValue(Command param, QColor value) {
    switch(param) {
        case FontColor: {
            m_fontColor = value;
            break;
        }
        case BackgroundColor: {
            m_backgroundColor = value;
            break;
        }
        case BorderColor:  {
            m_borderColor = value;
            break;
        }
        case FrameTop: {
            m_borderTopColor = value;
            break;
        }
        case FrameBottom: {
            m_borderBottomColor = value;
            break;
        }
        case FrameLeft: {
            m_borderLeftColor = value;
            break;
        }
        case FrameRight: {
            m_borderRightColor = value;
            break;
        }
        default: return;
    }
}

//Check, is there any side
bool GraphicsHelperClass::borderIsCheck(Command command) {
    QColor color;
    if (command == FrameTop)
        color = m_borderTopColor;
    if (command == FrameLeft)
        color = m_borderLeftColor;
    if (command == FrameRight)
        color = m_borderRightColor;
    if (command == FrameBottom)
        color = m_borderBottomColor;

    if ( (color.red() != 255) && (color.green() != 255) && (color.blue() != 255) ) {
        return true;
    }
    else {
        return false;
    }
}

void GraphicsHelperClass::setBorder(Command command, QVariant values, bool yesFrame) {
    QColor color = values.value<QColor>();
    if (color.isValid()) {
        m_borderColor = color;
    } else {
        color = getColorValue(BorderColor);
    }
    m_borderColor = color;

    switch(command) {
        case None: {
            if (getColorValue(FrameTop) != Qt::black)
                m_borderTopColor = color;
            if (getColorValue(FrameBottom) != Qt::black)
                m_borderBottomColor = color;
            if (getColorValue(FrameLeft) != Qt::black)
                m_borderLeftColor = color;
            if (getColorValue(FrameRight) != Qt::black)
                m_borderRightColor = color;
            break;
        }
        case FrameNo: {
            m_borderLeftColor = Qt::white;
            m_borderRightColor = Qt::white;
            m_borderTopColor = Qt::white;
            m_borderBottomColor = Qt::white;
            break;
        }
        case FrameAll: {
            m_borderLeftColor = m_borderColor;
            m_borderRightColor = m_borderColor;
            m_borderTopColor = m_borderColor;
            m_borderBottomColor = m_borderColor;
            break;
        }
        case FrameTop: {
            if (!yesFrame) m_borderTopColor = Qt::white;
            else m_borderTopColor = m_borderColor;
            break;
        }
        case FrameBottom: {
            if (!yesFrame) m_borderBottomColor = Qt::white;
            else m_borderBottomColor = m_borderColor;
            break;
        }
        case FrameRight: {
            if (!yesFrame) m_borderRightColor = Qt::white;
            else m_borderRightColor = m_borderColor;
            break;
        }
        case FrameLeft: {
            if (!yesFrame) m_borderLeftColor = Qt::white;
            else m_borderLeftColor = m_borderColor;
            break;
        }
        case FrameStyle: {
            BorderStyle borderStyle = (BorderStyle)values.toInt();
            switch(borderStyle) {
                case Solid: {
                    m_borderStyle = Qt::SolidLine;
                    break;
                }
                case Dashed: {
                    m_borderStyle = Qt::DashLine;
                    break;
                }
                case Dotted: {
                    m_borderStyle = Qt::DotLine;
                    break;
                }
                case Dot_dash: {
                    m_borderStyle = Qt::DashDotLine;
                    break;
                }
                case Dot_dot_dash: {
                    m_borderStyle = Qt::DashDotDotLine;
                    break;
                }
                case Double: {
                    m_borderStyle = Qt::CustomDashLine;
                    break;
                }
                default: return;
            }
            break;
        }
        case FrameWidth: {
            borderWidth = values.toInt();
            break;
        }
        default: return;
    }
}

void GraphicsHelperClass::setBorderWidth(int value) {
    borderWidth = value;
}

int GraphicsHelperClass::getBorderWidth() {
    return borderWidth;
}

GraphicsHelperClass::~GraphicsHelperClass() {
    emit itemDeleting(this->itemInTree);
}

void GraphicsHelperClass::edit() {
    if (graphicsItem->type() == ItemType::GBox) {
        GraphicsHelperList selContList;
        selContList.append(this);
        //before changing params gets params
        BArrayList oldList = ParamCommand::getBArrayFromContList(selContList);

        EditFldDlg *dlg = new EditFldDlg(getMW());
        switch(m_type) {
            case Text:
            case TextImage:
            case DatabaseImage: {
                dlg->showText(graphicsItem);
                break;
            }
            case TextRich: {
                dlg->showTextRich(graphicsItem);
                break;
            }
            case Image: {
                dlg->showImage(graphicsItem);
                break;
            }
            case Diagram: {
                dlg->showDiagram(graphicsItem);
                break;
            }
            case Barcode: {
                dlg->showBarcode(graphicsItem);
                break;
            }
            case CrossTab: {
                dlg->showCrosstab(graphicsItem);
                break;
            }
            default: return;
        }
        if (dlg->result() == QDialog::Accepted) {
            getMW()->setReportChanged();

            //gets new params
            BArrayList newList = ParamCommand::getBArrayFromContList(selContList);
            QList<PairCont> lst = ParamCommand::compoundArrays(oldList,newList);

            GraphicsScene *scene = qobject_cast<GraphicsScene*>(graphicsItem->scene());
            scene->m_undoStack->push( new ParamCommand( lst, scene ) );
        }

        delete dlg;
    }
}

void GraphicsHelperClass::moveForward() {
    graphicsItem->setZValue(graphicsItem->zValue()+1);
}

void GraphicsHelperClass::moveBack() {
    graphicsItem->setZValue(graphicsItem->zValue()-1);
}

void GraphicsHelperClass::loadParamFromXML(QDomElement e) {
    m_type = QtRPT::getFieldType(e);
    this->setObjectName(e.attribute("name"));
    this->m_printing = e.attribute("printing","1");
    this->m_groupName = e.attribute("groupName","");
    this->borderWidth = e.attribute("borderWidth","1px").replace("px","").toInt();
    this->setColorValue(BorderColor, colorFromString(e.attribute("borderColor","rgba(0,0,0,255)")));
    this->m_borderStyle = QtRPT::getPenStyle(e.attribute("borderStyle","solid"));
    this->graphicsItem->setZValue(e.attribute("ZValue","11").toInt());
}

QDomElement GraphicsHelperClass::saveParamToXML(QDomDocument *xmlDoc) {
    QDomElement elem;
    if (graphicsItem->type() == ItemType::GBox) {
        elem = xmlDoc->createElement("TContainerField");
    }
    if (graphicsItem->type() == ItemType::GLine) {
        elem = xmlDoc->createElement("TContainerLine");
    }
    elem.setAttribute("type",QtRPT::getFieldTypeName(m_type));
    elem.setAttribute("name",this->objectName());
    elem.setAttribute("printing",this->getPrinting());
    elem.setAttribute("groupName",this->getGroupName());
    elem.setAttribute("borderWidth",QString::number(getBorderWidth())+"px");
    elem.setAttribute("borderColor",colorToString(m_borderColor));
    elem.setAttribute("borderStyle",setPenStyle(m_borderStyle));
    elem.setAttribute("ZValue",graphicsItem->zValue());
    return elem;
}

QString GraphicsHelperClass::setPenStyle(Qt::PenStyle style) {
    QString str;
    if (style == Qt::SolidLine) str = "solid";
    else if (style == Qt::DashLine) str = "dashed";
    else if (style == Qt::DotLine) str = "dotted";
    else if (style == Qt::DashDotLine) str = "dot-dash";
    else if (style == Qt::DashDotDotLine) str = "dot-dot-dash";
    else str = "SolidLine";
    return str;
}

bool GraphicsHelperClass::helperIsSelected() {
    if (itemInTree != nullptr)
        return itemInTree->isSelected();
    return false;
}

void GraphicsHelperClass::helperSelect(bool value) {
    if (graphicsItem->type() == ItemType::GBox || graphicsItem->type() == ItemType::GBand) {
        GraphicsBox *box = static_cast<GraphicsBox*>(graphicsItem);
        box->setSelected(value);
    }
    if (graphicsItem->type() == ItemType::GLine) {
        GraphicsLine *line = static_cast<GraphicsLine*>(graphicsItem);
        line->setSelected(value);
    }
}

QDataStream &operator<<(QDataStream &stream, const GraphicsHelperClass &obj) {
    for(int i=0; i<obj.metaObject()->propertyCount(); ++i) {
        if(obj.metaObject()->property(i).isStored(&obj)) {
            stream << obj.metaObject()->property(i).read(&obj);
        }
    }
    QList<QByteArray> list = obj.dynamicPropertyNames();
    for (int i=0; i<list.size(); i++) {
        stream << obj.property(list.at(i));
    }
    GraphicsBox *item = static_cast<GraphicsBox*>(obj.graphicsItem);

    if (item->type() == ItemType::GBox ) {
        stream << item->getText();
        stream << item->getFont();
    }

    if (obj.m_type == Diagram) {
        item->getChart()->setProperties();
        stream << *item->getChart();
    }
    if (obj.m_type == Barcode) {
        item->getBarCode()->setProperties();
        stream << *item->getBarCode();
    }

    return stream;
}

QDataStream &operator>>(QDataStream &stream, GraphicsHelperClass &obj) {
    QVariant var;
    for(int i=0; i<obj.metaObject()->propertyCount(); ++i) {
        if(obj.metaObject()->property(i).isStored(&obj)) {
            stream >> var;
            if (!var.isNull())
                obj.metaObject()->property(i).write(&obj, var);
        }
    }
    //obj.setProperties();
    QList<QByteArray> list = obj.dynamicPropertyNames();
    for (int i=0; i<list.size(); i++) {
        stream >> var;
        obj.setProperty(list.at(i),QVariant(var));
    }
    GraphicsBox *item = static_cast<GraphicsBox*>(obj.graphicsItem);

    if (item->type() == ItemType::GBox ) {
        QString text;
        stream >> text;
        item->setText(text);
        QFont font;
        stream >> font;
        item->setFont(font);
    }

    if (obj.m_type == Diagram) {
        /*
         * Chart *chart = item->getChart();
        chart = new Chart(0);
*/
        stream >> *item->getChart();
    }
    if (obj.m_type == Barcode) {
        /*
        BarCode *barcode = item->getBarCode();
        barcode = new BarCode(0);
*/
        stream >> *item->getBarCode();
    }
    //obj.setParamFromProperties();

    return stream;
}
