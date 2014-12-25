#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSettings>
#include <QDataWidgetMapper>
#include <QMessageBox>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_dialog_closed();

signals:
    void sendMode(QString mode, QString num);

private slots:
    void on_exit_triggered();
    void on_mCreatedb_triggered();
    void on_mSettings_triggered();
    void on_rbAll_clicked(bool checked);
    void on_rbCompleted_clicked(bool checked);
    void on_rbAccepted_clicked(bool checked);
    void on_rbConsent_clicked(bool checked);
    void on_rbWaitSpares_clicked(bool checked);
    void on_searchbydate_clicked();
    void on_lSearch_textEdited(const QString &arg1);
    void on_bSubmit_clicked();
    void on_mNewOrder_triggered();
    void on_bView_clicked();
    void on_bEdit_clicked();
    void on_mEmployees_triggered();
    void on_mInit_triggered();
    void on_bDelete_clicked();
    void on_mConstants_triggered();
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

private:
    bool dbConnect();
    Ui::MainWindow *ui;
    void initModelOrders();
    void getCustomerIds();
    void initDataMapper();
    void editDone();
    void showEditOrder();
    void showEditWorkReport();
    void showEditDiagReport();
    void showGiveOrder();
    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;
    int customerIdx, stateIdx, masterIdx, typeIdx, acceptorIdx, giverIdx;
    QString namesstr;
};

#endif // MAINWINDOW_H
