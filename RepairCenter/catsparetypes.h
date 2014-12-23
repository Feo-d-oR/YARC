#ifndef CATSPARETYPES_H
#define CATSPARETYPES_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class CatSpareTypes;
}

class CatSpareTypes : public QDialog
{
    Q_OBJECT

public:
    explicit CatSpareTypes(QWidget *parent = 0);
    ~CatSpareTypes();

private slots:
    void on_bAdd_clicked();
    void on_bSave_clicked();
    void on_bClose_clicked();
    void on_bDelete_clicked();

private:
    Ui::CatSpareTypes *ui;
    QSqlTableModel *model;
    void initModel();
};

#endif // CATSPARETYPES_H
