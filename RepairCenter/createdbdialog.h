#ifndef CREATEDBDIALOG_H
#define CREATEDBDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QSettings>
#include <QMessageBox>

namespace Ui {
class CreateDBDialog;
}

class CreateDBDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateDBDialog(QWidget *parent = 0);
    ~CreateDBDialog();

private slots:
    void on_close_clicked();
    void on_create_clicked();

private:
    bool dbCheckConnect();
    QSqlError createDatabase();
    void saveSettings();
    Ui::CreateDBDialog *ui;
};

#endif // CREATEDBDIALOG_H
