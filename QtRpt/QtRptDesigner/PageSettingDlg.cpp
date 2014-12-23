/*
Name: QtRptDesigner
Version: 1.4.5
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net
2012-2014
*/

#include <QSettings>
#include <QtDebug>
#include "PageSettingDlg.h"
#include "ui_PageSettingDlg.h"

PageSettingDlg::PageSettingDlg(QWidget *parent) : QDialog(parent), ui(new Ui::PageSettingDlg) {
    ui->setupUi(this);
    QObject::connect(ui->rLandscape, SIGNAL(clicked()), this, SLOT(changeOrientation()));
    QObject::connect(ui->rPortrait, SIGNAL(clicked()), this, SLOT(changeOrientation()));
    QObject::connect(ui->cbPageSize, SIGNAL(currentIndexChanged(int)), this, SLOT(pageSizeChanged(int)));
}

void PageSettingDlg::showThis(PageSetting pageSetting) {
    QSettings settings(QCoreApplication::applicationDirPath()+"/setting.ini",QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    settings.beginGroup("language");
    QString measurement = settings.value("measurement").toString();
    settings.endGroup();
    QString meas_label;

    if (measurement == "" || measurement == "Cm") {
        meas_label = tr("Cm");
        koef = 40;
    } else if (measurement == "Inch") {
        meas_label = tr("Inch");
        koef = 101.59;
    }

    if (pageSetting.pageWidth == w_A4 && pageSetting.pageHeight == h_A4) ui->cbPageSize->setCurrentIndex(0);
    else if (pageSetting.pageWidth == w_Lt && pageSetting.pageHeight == h_Lt) ui->cbPageSize->setCurrentIndex(1);
    else ui->cbPageSize->setCurrentIndex(0);

    ui->label->setText(meas_label);
    ui->label_2->setText(meas_label);
    ui->label_3->setText(meas_label);
    ui->label_4->setText(meas_label);
    ui->label_12->setText(meas_label);
    ui->label_13->setText(meas_label);

    ui->edtLeft->setText(QString::number(pageSetting.marginsLeft/koef, 'f', 2));
    ui->edtRight->setText(QString::number(pageSetting.marginsRight/koef, 'f', 2));
    ui->edtTop->setText(QString::number(pageSetting.marginsTop/koef, 'f', 2));
    ui->edtBottom->setText(QString::number(pageSetting.marginsBottom/koef, 'f', 2));
    ui->edtWidth->setText(QString::number(pageSetting.pageWidth/koef, 'f', 2));
    ui->edtHeight->setText(QString::number(pageSetting.pageHeight/koef, 'f', 2));

    if (pageSetting.pageOrientation == 0) ui->rPortrait->setChecked(true);
    if (pageSetting.pageOrientation == 1) ui->rLandscape->setChecked(true);
    if (ui->rLandscape->isChecked())
        ui->lblOrientation->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/landscape.png")));
    if (ui->rPortrait->isChecked())
        ui->lblOrientation->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/portrait.png")));
    if (exec() == QDialog::Accepted) {
        saveSettings();
    }
}

void PageSettingDlg::pageSizeChanged(int index) {
    switch(index) {
        case 0: //A4
            ui->edtWidth->setText(QString::number(w_A4/koef,'f',2));
            ui->edtHeight->setText(QString::number(h_A4/koef,'f',2));
            break;
        case 1: //Letter
            ui->edtWidth->setText(QString::number(w_Lt/koef,'f',2));
            ui->edtHeight->setText(QString::number(h_Lt/koef,'f',2));
            break;
    }
}

void PageSettingDlg::changeOrientation() {
    QString str = ui->edtHeight->text();
    ui->edtHeight->setText(ui->edtWidth->text());
    ui->edtWidth->setText(str);
    if (ui->rLandscape->isChecked())
        ui->lblOrientation->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/landscape.png")));
    if (ui->rPortrait->isChecked())
        ui->lblOrientation->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/portrait.png")));
}

void PageSettingDlg::saveSettings() {
    pageSetting.marginsLeft   = QString::number(ui->edtLeft->text().toFloat()*koef,'f',0).toFloat();
    pageSetting.marginsRight  = QString::number(ui->edtRight->text().toFloat()*koef,'f',0).toFloat();
    pageSetting.marginsTop    = QString::number(ui->edtTop->text().toFloat()*koef,'f',0).toFloat();
    pageSetting.marginsBottom = QString::number(ui->edtBottom->text().toFloat()*koef,'f',0).toFloat();
    pageSetting.pageWidth     = QString::number(ui->edtWidth->text().toFloat()*koef,'f',0).toFloat();
    pageSetting.pageHeight    = QString::number(ui->edtHeight->text().toFloat()*koef,'f',0).toFloat();
    if (ui->rLandscape->isChecked())
        pageSetting.pageOrientation = 1;
    if (ui->rPortrait->isChecked())
        pageSetting.pageOrientation = 0;
}

PageSettingDlg::~PageSettingDlg() {
    delete ui;
}
