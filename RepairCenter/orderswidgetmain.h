#ifndef ORDERSWIDGETMAIN_H
#define ORDERSWIDGETMAIN_H

#include <QWidget>
#include <QtSql>
#include <QSettings>
#include <QDataWidgetMapper>
#include <QMessageBox>
#include <QDesktopServices>

namespace Ui {
class OrdersWidgetMain;
}

class OrdersWidgetMain : public QWidget
{
    Q_OBJECT

public:
    explicit OrdersWidgetMain(QWidget *parent = 0);
    ~OrdersWidgetMain();

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
    void on_bSubmit_clicked();
    void on_bView_clicked();
    void on_bEdit_clicked();
    void on_bDelete_clicked();
    void on_tview_clicked(const QModelIndex &index);
    void on_eCalled_stateChanged(int state);
    void on_searchbyfield_clicked();
    void on_lSearch_returnPressed();

private:
    Ui::OrdersWidgetMain *ui;
    void initModelOrders();
    void readUiSettings();
    void showEditOrder();
    void searchByField();
    QSettings * settings;
    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;
    int customerIdx, stateIdx, masterIdx, typeIdx, acceptorIdx, giverIdx;
    QString namesstr;
    QString currentID;
};

#endif // ORDERSWIDGETMAIN_H
