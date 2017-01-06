#ifndef PARTSREQLOG_H
#define PARTSREQLOG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class PartsReqLog;
}

class PartsReqLog : public QDialog
{
    Q_OBJECT

public:
    explicit PartsReqLog(QWidget *parent = 0);
    ~PartsReqLog();

private slots:
    void on_bClose_clicked();
    void on_eEmployee_activated(int index);
    void on_eOrderID_returnPressed();
    void on_bSearchByDate_clicked();
    void on_bClear_clicked();
    void on_eRequestID_returnPressed();

private:
    Ui::PartsReqLog *ui;
    QSqlRelationalTableModel *model;
    QSqlQueryModel *model_e;
    QSqlRecord rec_e;
    QString id_e;
    void initModels();
    int employee_idx;
    int state_idx;
};

#endif // PARTSREQLOG_H
