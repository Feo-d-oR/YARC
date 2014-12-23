#ifndef CATWORKTYPES_H
#define CATWORKTYPES_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class CatWorkTypes;
}

class CatWorkTypes : public QDialog
{
    Q_OBJECT

public:
    explicit CatWorkTypes(QWidget *parent = 0);
    ~CatWorkTypes();

private slots:
    void on_bAdd_clicked();
    void on_bSave_clicked();
    void on_bClose_clicked();
    void on_bDelete_clicked();

    void on_eSearchText_textEdited(const QString &arg1);

private:
    Ui::CatWorkTypes *ui;
    QSqlTableModel *model;
    void initModel();
};

#endif // CATWORKTYPES_H
