/*
Name: QtRptDesigner
Version: 1.4.5
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net012-2014
*/

#ifndef FLDPROPERTYDLG_H
#define FLDPROPERTYDLG_H

#include <QDialog>

namespace Ui {
class FldPropertyDlg;
}

class FldPropertyDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit FldPropertyDlg(QWidget *parent = 0);
    ~FldPropertyDlg();
    QString showThis(int index, QWidget *widget = 0, QString value = 0);
    
private:
    Ui::FldPropertyDlg *ui;

private slots:
    void changeCategory(int row);
    void changeFormat(int row);
    void precisionChanged(int row);

};

#endif // FLDPROPERTYDLG_H
