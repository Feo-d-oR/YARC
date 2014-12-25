#ifndef EDITWORKREPORT_H
#define EDITWORKREPORT_H

#include <QDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QtSql>

namespace Ui {
class EditWorkReport;
}

class EditWorkReport : public QDialog
{
    Q_OBJECT

public:
    explicit EditWorkReport(QWidget *parent = 0);
    ~EditWorkReport();

signals:
    void reportSubmited();

private:
    Ui::EditWorkReport *ui;
    QSqlQuery qf;
    QSqlQuery qfs;
    QSqlRecord recf;
    QSqlRecord recfs;
    void submitReport();
    void fillFields();
    void setModels();
    bool saved;
    int i;
    QString reportID;
    QString orderID;
    QString id_s;
    QStringList lsp;
    QStringList lqt;
    QSqlQueryModel *model_m;
    QSqlTableModel *model_w;
    QSqlTableModel *model_s;

protected:
    void closeEvent(QCloseEvent *event);

public slots:
   void getMode(QString mode, QString num);

private slots:
   void on_bCancel_clicked();
   void on_bSave_clicked();
   void on_bAddWork_clicked();
   void on_bUse_clicked();
   void on_bRemove_clicked();
   void on_eSpare_currentIndexChanged(int index);
   void on_eWork_currentIndexChanged(int index);
   void on_bAddSpare_clicked();
};

#endif // EDITWORKREPORT_H
