#ifndef ORDERSLOG_H
#define ORDERSLOG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class OrdersLog;
}

class OrdersLog : public QDialog
{
    Q_OBJECT

public:
    explicit OrdersLog(QWidget *parent = 0);
    ~OrdersLog();

private slots:
    void on_bClose_clicked();
    void on_eEmployee_activated(int index);
    void on_eOrderID_returnPressed();
    void on_bSearchByDate_clicked();
    void on_bClear_clicked();

private:
    Ui::OrdersLog *ui;
    QSqlRelationalTableModel *model;
    QSqlQueryModel *model_e;
    QSqlRecord rec_e;
    QString id_e;
    void initModels();
    int employee_idx;
    int state_idx;
};

#endif // ORDERSLOG_H
