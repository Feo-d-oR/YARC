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
    void on_mExit_triggered();

private:
    bool dbCheckConnect();
    void saveSettings();
    bool connectDB();
    void readSettings();
    int dbversion;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
