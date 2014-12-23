/*
Name: QtRptDesigner
Version: 1.4.5
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net
2012-2014
*/

#ifndef SETTINGDLG_H
#define SETTINGDLG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
    class SettingDlg;
}

class SettingDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDlg(QWidget *parent = 0);
    void showThis();
    ~SettingDlg();

private:
    Ui::SettingDlg *ui;
    int langIndex;
};

#endif // SETTINGDLG_H
