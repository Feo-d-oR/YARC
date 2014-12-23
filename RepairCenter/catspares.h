#ifndef CATSPARES_H
#define CATSPARES_H

#include <QDialog>
#include <QtSql>
#include <QDataWidgetMapper>

namespace Ui {
class CatSpares;
}

class CatSpares : public QDialog
{
    Q_OBJECT

public:
    explicit CatSpares(QWidget *parent = 0);
    ~CatSpares();

private slots:
    void on_bAdd_clicked();
    void on_bSave_clicked();
    void on_bClose_clicked();
    void on_bDelete_clicked();
    void on_cSearchType_currentIndexChanged(int index);
    void on_eSearchName_textEdited(const QString &arg1);
    void on_bClear_clicked();

private:
    Ui::CatSpares *ui;
    QSqlRelationalTableModel *model;
    QSqlTableModel *model_t;
    QDataWidgetMapper *mapper;
    QSqlQuery qst;
    void initModels();
    int type_idx;
    QSqlRecord rec_t;
    QString id_t;
};

#endif // CATSPARES_H
