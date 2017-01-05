#include "qdynamiccheckbox.h"

qDynamicCheckBox::qDynamicCheckBox(QWidget *parent) :
    QCheckBox(parent)
{
    checkID++;
    chboxID = QString::number(checkID);
}

qDynamicCheckBox::~qDynamicCheckBox()
{

}

QString qDynamicCheckBox::getID()
{
    return chboxID;
}

void qDynamicCheckBox::setID(QString id)
{
    chboxID = id;
}

int qDynamicCheckBox::checkID = 0;

