#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QSettings>
#include <QMessageBox>
#include <QProcess>
#include <QtSql>
#include <QCryptographicHash>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

private slots:
    void on_cancel_clicked();
    void on_save_clicked();
    void on_ePassword_textEdited(const QString &arg1);

private:
    Ui::Settings *ui;
    int langIdx;
    QSettings * settings;
    QSqlQuery q;
    QSqlQueryModel *model_a;
    QSqlQueryModel *model_m;
    QSqlQueryModel *model_s;
    QString st;
    QByteArray pwdhash;
    QString pwdhashstr;
    bool user_changed;
    bool db_changed;
};

#endif // DBSETTINGSDIALOG_H
