/*
Name: QtRptDesigner
Version: 1.4.5
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net
2012-2014
*/

#include "aboutDlg.h"

AboutDlg::AboutDlg(QWidget *parent) : QDialog(parent) {
    this->setWindowTitle(tr("About QtRptDesiner"));
    QSize MaxSize(380, 300);
    QSize MinSize(380, 300);
    setMaximumSize(MaxSize);
    setMinimumSize(MinSize);

    QRect gry = geometry();
    gry.moveCenter(qApp->desktop()->availableGeometry().center());
    setGeometry(gry);

    QPushButton *btnOK = new QPushButton(this);
    btnOK->setText("OK");
    QObject::connect(btnOK, SIGNAL(clicked()), this, SLOT(close()));

    QLabel *labImg = new QLabel(this);
    labImg->setPixmap(QPixmap(":/new/prefix1/images/Logo128.png"));
    QString lbl1 = "<h2><b><p style='color:#0033FF'>"+QApplication::applicationName()+"</p></b></h2>"+
                  tr("Version: ")+QApplication::applicationVersion()+"<br>"+
                  tr("Programmer: Aleksey Osipov")+"<br>"+
                  "E-mail: aliks-os@ukr.net"+"<br>"+
                  "<a href='https://sourceforge.net/projects/qtrpt/'>https://sourceforge.net/projects/qtrpt/</a>"+"<br>"+
                  tr("2012-2014 years")+"<br><br>";
    QString lbl2 = tr("Thanks to:")+
                  "<ul>"+
                  "<li>"+tr("Lukas Lalinsky for DBmodel")+"</li>"+
                  "<li>"+tr("Muhamad Bashir Al-Noimi for Arabic translation")+"</li>"+
                  "<li>"+tr("Luis Brochado for Portuguese translation")+"</li>"+
                  "<li>"+tr("Li Wei for Chinese translation")+"</li>"+
                  "</ul>";
    QLabel *lab1 = new QLabel(lbl1, this);
    QObject::connect(lab1, SIGNAL(linkActivated(const QString)), this, SLOT(openLink(const QString)));
    QLabel *lab2 = new QLabel(lbl2, this);

    QHBoxLayout *hLayout2 = new QHBoxLayout;
    hLayout2->addWidget(labImg);
    hLayout2->addWidget(lab1);
    hLayout2->addStretch();

    QHBoxLayout *hLayout1 = new QHBoxLayout;
    //hLayout->addSpacerItem(spacer1);
    hLayout1->addStretch();
    hLayout1->addWidget(btnOK);
    //hLayout->addSpacerItem(spacer2);
    hLayout1->addStretch();

    QVBoxLayout *vLayout = new QVBoxLayout;
    //vLayout->addSpacerItem(spacer3);
    vLayout->addLayout(hLayout2);
    vLayout->addWidget(lab2);
    vLayout->addStretch();
    vLayout->addLayout(hLayout1);
    this->setLayout(vLayout);
}

void AboutDlg::openLink(const QString url) {
    QDesktopServices::openUrl(QUrl(url));
}
