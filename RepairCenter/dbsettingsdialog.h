#ifndef DBSETTINGSDIALOG_H
#define DBSETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class DBSettingsDialog;
}

class DBSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DBSettingsDialog(QWidget *parent = 0);
    ~DBSettingsDialog();

private slots:
    void on_cancel_clicked();

    void on_save_clicked();

private:
    Ui::DBSettingsDialog *ui;
};

#endif // DBSETTINGSDIALOG_H
