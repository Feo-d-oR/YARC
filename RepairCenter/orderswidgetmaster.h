#ifndef ORDERSWIDGETMASTER_H
#define ORDERSWIDGETMASTER_H

#include <QWidget>
#include <QtSql>
#include <QSettings>
#include <QDataWidgetMapper>
#include <QMessageBox>
#include <QDesktopServices>

namespace Ui {
class OrdersWidgetMaster;
}

class OrdersWidgetMaster : public QWidget
{
    Q_OBJECT

public:
    explicit OrdersWidgetMaster(QWidget *parent = 0);
    ~OrdersWidgetMaster();

public slots:
    void on_dialog_closed();
    void on_reconnect_recieved();

signals:
    void sendMode(QString mode, QString num);

private slots:
    void on_rbAll_clicked(bool checked);
    void on_rbCompleted_clicked(bool checked);
    void on_rbAccepted_clicked(bool checked);
    void on_rbConsent_clicked(bool checked);
    void on_rbWaitSpares_clicked(bool checked);
    void on_rbCall_clicked(bool checked);
    void on_searchbydate_clicked();
    void on_lSearch_textEdited(const QString &arg1);
    void on_bSubmit_clicked();
    void on_tview_clicked(const QModelIndex &index);
    void on_cbSearchMaster_activated(int index);

private:
    Ui::OrdersWidgetMaster *ui;
    void initModelOrders();
    void initModelMasters();
    void readUiSettings();
    QSettings * settings;
    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;
    QSqlQueryModel * model_m;
    int customerIdx, stateIdx, masterIdx, typeIdx, acceptorIdx, giverIdx;
    QString namesstr;
    QString currentID;
};

#endif // ORDERSWIDGETMASTER_H
