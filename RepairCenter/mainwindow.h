#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSettings>
#include <QDataWidgetMapper>
#include <QMessageBox>
#include <QPushButton>
#include <QDesktopServices>
#include <QCryptographicHash>
#include "simplecrypt.h"
#include "orderswidgetmain.h"
#include "orderswidgetmaster.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static QString sLocale;
    static float sPercMast;
    static float sPercAcc;
    static float sPercFirm;
    static QString prevCustomer;
    static int defAcceptor;
    static int defMaster;
    static int defState;
    static int role;
    static bool masterCanEditWorks;
    static bool masterCanEditSpares;
    static bool acceptorCanEditWorks;
    static bool acceptorCanEditSpares;
    static bool acceptorCanEditDiag;
    static bool isadmin;
    static QString currentID;
    static QString showlimit;
    static bool limitallfilters;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

//public slots:
//    void on_dialog_closed();

signals:
    void sendMode(QString mode, QString num);
    void sendReconnect();

private slots:
    void on_exit_triggered();
    void on_mSettings_triggered();
    void on_mNewOrder_triggered();
    void on_mEmployees_triggered();
    void on_mInit_triggered();
    void on_mProductTypes_triggered();
    void on_mCustomers_triggered();
    void on_mSpares_triggered();
    void on_mSpareTypes_triggered();
    void on_mWorkTypes_triggered();
    void on_mJrnWorkReports_triggered();
    void on_mNewWorkReport_triggered();
    void on_mGiveOrder_triggered();
    void on_mAbout_triggered();
    void on_mJrnDiagReports_triggered();
    void on_mNewDiagReport_triggered();
    void on_mGiveOrderDiag_triggered();
    void on_mHelp_triggered();
    void on_mPrintHWDocs_triggered();
    void on_mAboutQt_triggered();
    void on_mPaySalaries_triggered();
    void on_mSuppliers_triggered();
    void on_mNewPartsRequest_triggered();
    void on_mJrnPartsRequests_triggered();

private:
    bool checkSettings();
    bool dbConnect();
    Ui::MainWindow *ui;
    void showEditOrder();
    void showEditWorkReport();
    void showEditDiagReport();
    void showGiveOrder();
    void showGiveOrderDiag();
    void showPartsRequest();
    void readGlobalSettings();
    void loadUserInterface();
    QSettings * settings;
    SimpleCrypt crypto;
//    OrdersWidgetMaster * ordersmast;
    QWidget * mainwidget;
//    OrdersWidgetMain * ordersmain;

protected:
    void closeEvent(QCloseEvent *event);
    void reject();
};

#endif // MAINWINDOW_H
