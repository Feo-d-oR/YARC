#ifndef EDITPARTSREQUEST_H
#define EDITPARTSREQUEST_H

#include <QDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QtSql>

namespace Ui {
class EditPartsRequest;
}

class EditPartsRequest : public QDialog
{
    Q_OBJECT

public:
    explicit EditPartsRequest(QWidget *parent = 0);
    ~EditPartsRequest();

signals:
    void requestSubmited();

private:
    Ui::EditPartsRequest *ui;
    QSqlQuery qf;
    QSqlQuery qfs;
    QSqlRecord recf;
    QSqlRecord recfs;
    void submitReport();
    void fillFields();
    void setModels();
    bool saved;
    bool isnew;
    int i;
    QString requestID;
    QString orderID;
    QString id_s;
    QStringList lsp;
    QStringList lqt;
    QSqlQueryModel *model_m;
    QSqlTableModel *model_s;
    QSqlQueryModel *model_st;

protected:
    void closeEvent(QCloseEvent *event);
    void reject();

public slots:
   void getMode(QString mode, QString num);

private slots:
   void on_bCancel_clicked();
   void on_bSave_clicked();
   void on_bUse_clicked();
   void on_bRemove_clicked();
   void on_eSpare_currentIndexChanged(int index);
};

#endif // EDITPARTSREQUEST_H
