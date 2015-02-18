#ifndef SALARIES_H
#define SALARIES_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class Salaries;
}

class Salaries : public QDialog
{
    Q_OBJECT

public:
    explicit Salaries(QWidget *parent = 0);
    ~Salaries();

private slots:
    void on_eEmployee_currentIndexChanged(int index);
    void on_bPayEmp_clicked();
    void on_bGetProfit_clicked();

private:
    Ui::Salaries *ui;
    QSqlQueryModel *model_e;
    QSqlQuery q;
    void calcSummEmpl();
    void calcSummFirm();
    void setModels();
    float summ;
    QString emplID;
    QString st;
    QSqlRecord rec_e;
};

#endif // SALARIES_H
