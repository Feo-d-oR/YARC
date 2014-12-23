/*
Name: QtRptDesigner
Version: 1.4.5
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net
2012-2014
*/

#ifndef EDITFLDDLG_H
#define EDITFLDDLG_H

#include <QDialog>
#include <QTextCharFormat>
#include "FldPropertyDlg.h"
#include "TContainerField.h"
#include "selectcolor.h"
#include "Barcode.h"

namespace Ui {
    class EditFldDlg;
}

class TContainerField;


class EditFldDlg : public QDialog
{
    Q_OBJECT

public:
    explicit EditFldDlg(QWidget *parent = 0);
    ~EditFldDlg();
    int showText(TContainerField *cont);
    int showTextRich(TContainerField *cont);
    int showImage(TContainerField *cont);
    int showDiagram(TContainerField *cont);
    int showBarcode(TContainerField *cont);

protected:

private:
    Ui::EditFldDlg *ui;
    bool boolImage;  //Proccess TextFiled as a Image
    TContainerField *m_cont;
    QString m_cond_printing;
    QString m_cond_higlighting;
    QString m_imgFormat;

private slots:
    void loadImage();
    void openProperty();
    void conditionalToggled(bool value);
    void backGroundToggled(bool value);
    void conditionChanged(const QString &text);
    void chooseColor();
    void encodeHighLightingString();
    void decodeHighLightingString();
    void autoFillData(bool value);
    void selectGraphColor();
    void moveRow();
    void itemSelectionChanged();
    void removeRow();
    void addRow();
    void setScaledContents(bool value);
    void update_preview();
    void textDirection();

};

#endif // EDITFLDDLG_H
