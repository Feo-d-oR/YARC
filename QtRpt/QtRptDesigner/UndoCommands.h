/*
Name: QtRptDesigner
Version: 1.4.5
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.ru
2012-2014
*/

#ifndef UNDOCOMMANDS_H
#define UNDOCOMMANDS_H

#include <QUndoCommand>
#include "RptContainer.h"
#include "TContainerField.h"
#include "ReportBand.h"
#include "mainwindow.h"

typedef QList<RptContainer *> RptContainerList;

struct PairCont {
    QByteArray first;
    RptContainer *second;
    FieldType third;
    QByteArray fifth;
};


class GeometryContainerCommand : public QUndoCommand
{
public:
    GeometryContainerCommand(const RptContainerList contList, QUndoCommand *parent = 0);
    void undo();
    void redo();

private:
    RptContainerList m_contList;
    QList<QRect> m_oldP1, m_oldP2, m_newP1, m_newP2;
};

//************************************************************************************************

class MainWindow;
class AddContainerCommand : public QUndoCommand
{
public:
    AddContainerCommand(RptContainerList contList, QUndoCommand *parent = 0);
    void undo();
    void redo();

private:   
    QWidget *pw;
    MainWindow *m_mainWindow;
    bool m_create;
    QList<PairCont> m_dataList;

};

//************************************************************************************************

class DelContainerCommand : public QUndoCommand
{
public:
    DelContainerCommand(RptContainerList contList, QUndoCommand *parent = 0);
    void undo();
    void redo();

private:
    QWidget *pw;
    MainWindow *m_mainWindow;
    bool m_create;
    QList<PairCont> m_dataList;

};

//************************************************************************************************


typedef QList<QPair<QByteArray, RptContainer*> > BArrayList;

class ParamsContainerCommand : public QUndoCommand
{
public:
    ParamsContainerCommand(QList<PairCont> list, QUndoCommand *parent = 0);
    void undo();
    void redo();
    static BArrayList getBArrayFromContList(RptContainerList contList);
    static QList<PairCont> compoundArrays(BArrayList oldList, BArrayList newList);

private:
    bool m_create;
    QList<PairCont> m_dataList;

};

//************************************************************************************************

#endif // UNDOCOMMANDS_H
