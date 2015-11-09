#ifndef PARTSWIDGETSTOREKEEPER_H
#define PARTSWIDGETSTOREKEEPER_H

#include <QWidget>
#include <QtSql>
#include <QSettings>
#include <QDataWidgetMapper>
#include <QMessageBox>
#include <QDesktopServices>

namespace Ui {
class PartsWidgetStorekeeper;
}

class PartsWidgetStorekeeper : public QWidget
{
    Q_OBJECT

public:
    explicit PartsWidgetStorekeeper(QWidget *parent = 0);
    ~PartsWidgetStorekeeper();

public slots:
    void on_dialog_closed();
    void on_reconnect_recieved();

signals:
    void sendMode(QString mode, QString num);

private slots:
    void on_rbAll_clicked(bool checked);
    void on_rbActive_clicked(bool checked);
    void on_rbInfo_clicked(bool checked);
    void on_rbRecieve_clicked(bool checked);
    void on_rbGive_clicked(bool checked);
    void on_rbNew_clicked(bool checked);
    void on_bSubmit_clicked();
    void on_tview_clicked(const QModelIndex &index);
    void on_cbSearchMaster_activated(int index);
    void on_searchbyfield_clicked();
    void on_lSearch_returnPressed();
    void on_bView_clicked();
    void on_bEdit_clicked();
    void on_bDelete_clicked();

private:
    Ui::PartsWidgetStorekeeper *ui;
    void initModelRequests();
    void initModels();
    void readUiSettings();
    void showEditPartsRequest();
    void searchByField();
    QSettings * settings;
    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;
    QSqlQueryModel * model_m;
    QSqlQueryModel * model_s;
    int reqStateIdx, masterIdx, ordStateIdx;
    QString namesstr;
    QString currentID, orderID;
    QSqlQuery q;
    QSqlRecord rec;
    QSqlRecord rec_s;
    QString id_s;
    QModelIndexList idx_s;
    int orderState, newOrderState;
};

#endif // PARTSWIDGETSTOREKEEPER_H
