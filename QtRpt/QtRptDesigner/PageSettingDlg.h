/*
Name: QtRptDesigner
Version: 1.4.5
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net
2012-2014
*/

#ifndef PAGESETTINGDLG_H
#define PAGESETTINGDLG_H

#include <QDialog>

namespace Ui {
    class PageSettingDlg;
}

struct PageSetting {
    float marginsLeft;
    float marginsRight;
    float marginsTop;
    float marginsBottom;
    float pageWidth;
    float pageHeight;
    int pageOrientation;
};

class PageSettingDlg : public QDialog
{
    Q_OBJECT

public:
    explicit PageSettingDlg(QWidget *parent = 0);
    ~PageSettingDlg();
    void showThis(PageSetting pageSetting);
    PageSetting pageSetting;

private:
    static const int w_A4 = 840;
    static const int h_A4 = 1188;
    static const int w_Lt = 864;
    static const int h_Lt = 1115;
    double koef;
    Ui::PageSettingDlg *ui;
    void saveSettings();

private slots:
    void changeOrientation();
    void pageSizeChanged(int index);

};

#endif // PAGESETTINGDLG_H
