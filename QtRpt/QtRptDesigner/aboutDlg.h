/*
Name: QtRptDesigner
Version: 1.4.5
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net
2012-2014
*/

#ifndef ABOUTDLG_H
#define ABOUTDLG_H

#include <QWidget>
#include <QDialog>
#include <QtWidgets>

class AboutDlg : public QDialog {
    Q_OBJECT
public:
    explicit AboutDlg(QWidget *parent = 0);

signals:

private slots:
    void openLink(const QString url);
};

#endif // ABOUTDLG_H
