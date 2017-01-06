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
    QSqlQuery qf, qfs;
    QSqlRecord recf, recfs;
    void submitRequest();
    void fillFields();
    void setModels();
    void calcSumm();
    bool saved, isnew, holdCalc;
    int i, row;
    double summ;
    QString requestID, orderID, id_s;
    QStringList lsp, lqt;
    QSqlQueryModel *model_m, *model_st;
    QSqlTableModel *model_s;

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
   void on_tview_cellChanged(int row, int column);
};

#endif // EDITPARTSREQUEST_H
