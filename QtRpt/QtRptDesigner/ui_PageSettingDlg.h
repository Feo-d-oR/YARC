/********************************************************************************
** Form generated from reading UI file 'PageSettingDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGESETTINGDLG_H
#define UI_PAGESETTINGDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PageSettingDlg
{
public:
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_2;
    QComboBox *cbPageSize;
    QLabel *label_10;
    QLineEdit *edtWidth;
    QLabel *label_12;
    QLabel *label_11;
    QLineEdit *edtHeight;
    QLabel *label_13;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout;
    QRadioButton *rPortrait;
    QRadioButton *rLandscape;
    QLabel *lblOrientation;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLineEdit *edtLeft;
    QLabel *label;
    QLabel *label_7;
    QLineEdit *edtRight;
    QLabel *label_3;
    QLabel *label_6;
    QLineEdit *edtTop;
    QLabel *label_2;
    QLabel *label_8;
    QLineEdit *edtBottom;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOK;
    QPushButton *btnCancel;

    void setupUi(QDialog *PageSettingDlg)
    {
        if (PageSettingDlg->objectName().isEmpty())
            PageSettingDlg->setObjectName(QStringLiteral("PageSettingDlg"));
        PageSettingDlg->resize(347, 380);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PageSettingDlg->sizePolicy().hasHeightForWidth());
        PageSettingDlg->setSizePolicy(sizePolicy);
        PageSettingDlg->setMinimumSize(QSize(347, 380));
        PageSettingDlg->setMaximumSize(QSize(347, 380));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/images/pageSetting.png"), QSize(), QIcon::Normal, QIcon::Off);
        PageSettingDlg->setWindowIcon(icon);
        verticalLayout_4 = new QVBoxLayout(PageSettingDlg);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        groupBox_3 = new QGroupBox(PageSettingDlg);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        cbPageSize = new QComboBox(groupBox_3);
        cbPageSize->setObjectName(QStringLiteral("cbPageSize"));

        gridLayout_2->addWidget(cbPageSize, 0, 0, 1, 4);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_2->addWidget(label_10, 1, 0, 1, 1);

        edtWidth = new QLineEdit(groupBox_3);
        edtWidth->setObjectName(QStringLiteral("edtWidth"));

        gridLayout_2->addWidget(edtWidth, 1, 2, 1, 1);

        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_2->addWidget(label_12, 1, 3, 1, 1);

        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_2->addWidget(label_11, 2, 0, 1, 1);

        edtHeight = new QLineEdit(groupBox_3);
        edtHeight->setObjectName(QStringLiteral("edtHeight"));

        gridLayout_2->addWidget(edtHeight, 2, 2, 1, 1);

        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_2->addWidget(label_13, 2, 3, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 1, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout_2);


        verticalLayout_4->addWidget(groupBox_3);

        groupBox_2 = new QGroupBox(PageSettingDlg);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        rPortrait = new QRadioButton(groupBox_2);
        rPortrait->setObjectName(QStringLiteral("rPortrait"));
        rPortrait->setChecked(true);

        formLayout->setWidget(0, QFormLayout::LabelRole, rPortrait);

        rLandscape = new QRadioButton(groupBox_2);
        rLandscape->setObjectName(QStringLiteral("rLandscape"));

        formLayout->setWidget(1, QFormLayout::LabelRole, rLandscape);

        lblOrientation = new QLabel(groupBox_2);
        lblOrientation->setObjectName(QStringLiteral("lblOrientation"));
        lblOrientation->setText(QStringLiteral("TextLabel"));
        lblOrientation->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(0, QFormLayout::FieldRole, lblOrientation);


        verticalLayout_2->addLayout(formLayout);


        verticalLayout_4->addWidget(groupBox_2);

        groupBox = new QGroupBox(PageSettingDlg);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        edtLeft = new QLineEdit(groupBox);
        edtLeft->setObjectName(QStringLiteral("edtLeft"));

        gridLayout->addWidget(edtLeft, 0, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 2, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 0, 4, 1, 1);

        edtRight = new QLineEdit(groupBox);
        edtRight->setObjectName(QStringLiteral("edtRight"));

        gridLayout->addWidget(edtRight, 0, 5, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 6, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 1, 0, 1, 1);

        edtTop = new QLineEdit(groupBox);
        edtTop->setObjectName(QStringLiteral("edtTop"));

        gridLayout->addWidget(edtTop, 1, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 2, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 1, 4, 1, 1);

        edtBottom = new QLineEdit(groupBox);
        edtBottom->setObjectName(QStringLiteral("edtBottom"));

        gridLayout->addWidget(edtBottom, 1, 5, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 6, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);


        verticalLayout_4->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnOK = new QPushButton(PageSettingDlg);
        btnOK->setObjectName(QStringLiteral("btnOK"));

        horizontalLayout->addWidget(btnOK);

        btnCancel = new QPushButton(PageSettingDlg);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));

        horizontalLayout->addWidget(btnCancel);


        verticalLayout_4->addLayout(horizontalLayout);


        retranslateUi(PageSettingDlg);
        QObject::connect(btnOK, SIGNAL(clicked()), PageSettingDlg, SLOT(accept()));
        QObject::connect(btnCancel, SIGNAL(clicked()), PageSettingDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(PageSettingDlg);
    } // setupUi

    void retranslateUi(QDialog *PageSettingDlg)
    {
        PageSettingDlg->setWindowTitle(QApplication::translate("PageSettingDlg", "Page settings", 0));
        groupBox_3->setTitle(QApplication::translate("PageSettingDlg", "Size", 0));
        cbPageSize->clear();
        cbPageSize->insertItems(0, QStringList()
         << QApplication::translate("PageSettingDlg", "A4", 0)
         << QApplication::translate("PageSettingDlg", "Letter", 0)
        );
        label_10->setText(QApplication::translate("PageSettingDlg", "Width", 0));
        label_12->setText(QApplication::translate("PageSettingDlg", "cm", 0));
        label_11->setText(QApplication::translate("PageSettingDlg", "Height", 0));
        label_13->setText(QApplication::translate("PageSettingDlg", "cm", 0));
        groupBox_2->setTitle(QApplication::translate("PageSettingDlg", "Orientation", 0));
        rPortrait->setText(QApplication::translate("PageSettingDlg", "Portrait", 0));
        rLandscape->setText(QApplication::translate("PageSettingDlg", "Landscape", 0));
        groupBox->setTitle(QApplication::translate("PageSettingDlg", "Margins", 0));
        label_5->setText(QApplication::translate("PageSettingDlg", "Left", 0));
        label->setText(QApplication::translate("PageSettingDlg", "cm", 0));
        label_7->setText(QApplication::translate("PageSettingDlg", "Right", 0));
        label_3->setText(QApplication::translate("PageSettingDlg", "cm", 0));
        label_6->setText(QApplication::translate("PageSettingDlg", "Top", 0));
        label_2->setText(QApplication::translate("PageSettingDlg", "cm", 0));
        label_8->setText(QApplication::translate("PageSettingDlg", "Bottom", 0));
        label_4->setText(QApplication::translate("PageSettingDlg", "cm", 0));
        btnOK->setText(QApplication::translate("PageSettingDlg", "OK", 0));
        btnCancel->setText(QApplication::translate("PageSettingDlg", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class PageSettingDlg: public Ui_PageSettingDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGESETTINGDLG_H
