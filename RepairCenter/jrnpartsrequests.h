#ifndef JRNPARTSREQUESTS_H
#define JRNPARTSREQUESTS_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class JrnPartsRequests;
}

class JrnPartsRequests : public QDialog
{
    Q_OBJECT

public:
    explicit JrnPartsRequests(QWidget *parent = 0);
    ~JrnPartsRequests();

public slots:
    void on_dialog_closed();

signals:
    void sendMode(QString mode, QString num);

private slots:
    void on_bAdd_clicked();
    void on_bClose_clicked();
    void on_bDelete_clicked();
    void on_cSearchEmployee_currentIndexChanged(int index);
    void on_eSearchNumber_textEdited(const QString &arg1);
    void on_bClear_clicked();
    void on_bView_clicked();
    void on_bEdit_clicked();
    void on_tview_clicked(const QModelIndex &index);

private:
    Ui::JrnPartsRequests *ui;
    QSqlRelationalTableModel *model;
    QSqlTableModel *model_e;
    QSqlRecord rec_e;
    QString id_m;
    QString idpr;
    void initModels();
    void showEditPartRequest();
    int master_idx;
    int state_idx;

};

#endif // JRNPARTSREQUESTS_H
