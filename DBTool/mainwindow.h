#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSettings>
#include <QMessageBox>
#include <QDesktopServices>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_create_clicked();
    void on_bUpdate_clicked();
    void on_bClearSalary_clicked();
    void on_bClearOrders_clicked();
    void changeEvent(QEvent* event);
    void on_language_activated(int index);

private:
    bool dbCheckConnect();
    void saveSettings();
    bool connectDB();
    void readSettings();
    void allUpdated();
    void allCleared();
    void allLatest();
    void updateError(QSqlError error);
    int dbversion;
    Ui::MainWindow *ui;
    QSqlQuery q;
    QSqlError err;
    QSqlDatabase db;
    QTranslator qTranslator;
    QString locale;
    QString loSettings;
};

#endif // MAINWINDOW_H
