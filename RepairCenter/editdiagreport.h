#ifndef EDITDIAGREPORT_H
#define EDITDIAGREPORT_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <QCloseEvent>

namespace Ui {
class EditDiagReport;
}

class EditDiagReport : public QDialog
{
    Q_OBJECT

public:
    explicit EditDiagReport(QWidget *parent = 0);
    ~EditDiagReport();

signals:
    void reportSubmited();

private:
    Ui::EditDiagReport *ui;
    QSqlQuery qf;
    QSqlRecord recf;
    void submitReport();
    void fillFields();
    void setModels();
    bool isnew;
    bool saved;
    QString reportID;
    QString orderID;
    QSqlQueryModel *model_m;
    void checkExist();

protected:
    void closeEvent(QCloseEvent *event);
    void reject();

public slots:
   void getMode(QString mode, QString num);

private slots:
   void on_bCancel_clicked();
   void on_bSave_clicked();

   void on_eOrderID_textChanged(const QString &arg1);
};

#endif // EDITDIAGREPORT_H
