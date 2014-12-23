/*
Name: QtRptDesigner
Version: 1.4.5
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net
2012-2014
*/

#ifndef SQLDESIGNER_H
#define SQLDESIGNER_H

#include <QWidget>
#include <QDomDocument>
#include <QtSql>
#include "SQLHighlighter.h"
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QGraphicsScene>
//#include "diagramscene.h"
//#include "diagramitem.h"
#include "diagramdocument.h"
//#include "diagramtable.h"

namespace Ui {
class SqlDesigner;
}

class SqlDesigner : public QWidget
{
    Q_OBJECT

public:
    explicit SqlDesigner(QWidget *parent = 0);
    void showDataSource(QDomElement e);
    QDomElement saveParamToXML(QDomDocument *xmlDoc);
    ~SqlDesigner();

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::SqlDesigner *ui;
    QSqlDatabase db;
    DiagramDocument *scene;
    void refreshTable(QSqlDatabase *db);
    void newDiagramDocument();

private slots:
    void rbChecked();
    void connectDB();
    void btnClose();
    void addRelation();
    void clearDiagram();
    void undo();
    void redo();
    void select();
    void updateMode(DiagramDocument::Mode mode);
    void deleteSelected();
    void sqlChanged(const QString value);

signals:
    void changed(bool value);
};

#endif // SQLDESIGNER_H
