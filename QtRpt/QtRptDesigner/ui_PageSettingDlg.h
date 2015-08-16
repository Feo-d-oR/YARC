/********************************************************************************
** Form generated from reading UI file 'PageSettingDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGESETTINGDLG_H
#define UI_PAGESETTINGDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
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
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
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
    QLabel *lblOrientation;
    QRadioButton *rLandscape;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLineEdit *edtRight;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_7;
    QLineEdit *edtLeft;
    QLineEdit *edtBottom;
    QLabel *label_8;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_6;
    QLineEdit *edtTop;
    QGroupBox *groupBox_41;
    QVBoxLayout *verticalLayout_5;
    QGridLayout *gridLayout_4;
    QCheckBox *chkDrawBorder;
    QLabel *label_14;
    QLabel *lblBorderColor;
    QToolButton *btnBorderColor;
    QLabel *label_9;
    QSpinBox *spnBorderWidth;
    QLabel *label_15;
    QComboBox *cmbBorderStyle;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOK;
    QPushButton *btnCancel;

    void setupUi(QDialog *PageSettingDlg)
    {
        if (PageSettingDlg->objectName().isEmpty())
            PageSettingDlg->setObjectName(QStringLiteral("PageSettingDlg"));
        PageSettingDlg->resize(347, 450);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PageSettingDlg->sizePolicy().hasHeightForWidth());
        PageSettingDlg->setSizePolicy(sizePolicy);
        PageSettingDlg->setMinimumSize(QSize(347, 450));
        PageSettingDlg->setMaximumSize(QSize(347, 450));
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
        groupBox_2->setMinimumSize(QSize(0, 0));
        groupBox_2->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        rPortrait = new QRadioButton(groupBox_2);
        rPortrait->setObjectName(QStringLiteral("rPortrait"));
        rPortrait->setChecked(true);

        formLayout->setWidget(0, QFormLayout::LabelRole, rPortrait);

        lblOrientation = new QLabel(groupBox_2);
        lblOrientation->setObjectName(QStringLiteral("lblOrientation"));
        lblOrientation->setText(QStringLiteral("TextLabel"));
        lblOrientation->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(0, QFormLayout::FieldRole, lblOrientation);

        rLandscape = new QRadioButton(groupBox_2);
        rLandscape->setObjectName(QStringLiteral("rLandscape"));

        formLayout->setWidget(1, QFormLayout::LabelRole, rLandscape);


        verticalLayout_2->addLayout(formLayout);


        verticalLayout_4->addWidget(groupBox_2);

        groupBox = new QGroupBox(PageSettingDlg);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        edtRight = new QLineEdit(groupBox);
        edtRight->setObjectName(QStringLiteral("edtRight"));

        gridLayout->addWidget(edtRight, 0, 5, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 6, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 2, 6, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 0, 4, 1, 1);

        edtLeft = new QLineEdit(groupBox);
        edtLeft->setObjectName(QStringLiteral("edtLeft"));

        gridLayout->addWidget(edtLeft, 0, 1, 1, 1);

        edtBottom = new QLineEdit(groupBox);
        edtBottom->setObjectName(QStringLiteral("edtBottom"));

        gridLayout->addWidget(edtBottom, 2, 5, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 2, 4, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 2, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 2, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 2, 0, 1, 1);

        edtTop = new QLineEdit(groupBox);
        edtTop->setObjectName(QStringLiteral("edtTop"));

        gridLayout->addWidget(edtTop, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        verticalLayout_4->addWidget(groupBox);

        groupBox_41 = new QGroupBox(PageSettingDlg);
        groupBox_41->setObjectName(QStringLiteral("groupBox_41"));
        verticalLayout_5 = new QVBoxLayout(groupBox_41);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        chkDrawBorder = new QCheckBox(groupBox_41);
        chkDrawBorder->setObjectName(QStringLiteral("chkDrawBorder"));

        gridLayout_4->addWidget(chkDrawBorder, 0, 0, 1, 2);

        label_14 = new QLabel(groupBox_41);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_4->addWidget(label_14, 0, 2, 1, 1);

        lblBorderColor = new QLabel(groupBox_41);
        lblBorderColor->setObjectName(QStringLiteral("lblBorderColor"));
        lblBorderColor->setStyleSheet(QStringLiteral("QLabel {background-color: white}"));
        lblBorderColor->setFrameShape(QFrame::Box);
        lblBorderColor->setFrameShadow(QFrame::Sunken);

        gridLayout_4->addWidget(lblBorderColor, 0, 3, 1, 1);

        btnBorderColor = new QToolButton(groupBox_41);
        btnBorderColor->setObjectName(QStringLiteral("btnBorderColor"));

        gridLayout_4->addWidget(btnBorderColor, 0, 4, 1, 1);

        label_9 = new QLabel(groupBox_41);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_4->addWidget(label_9, 1, 0, 1, 1);

        spnBorderWidth = new QSpinBox(groupBox_41);
        spnBorderWidth->setObjectName(QStringLiteral("spnBorderWidth"));

        gridLayout_4->addWidget(spnBorderWidth, 1, 1, 1, 1);

        label_15 = new QLabel(groupBox_41);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_4->addWidget(label_15, 1, 2, 1, 1);

        cmbBorderStyle = new QComboBox(groupBox_41);
        cmbBorderStyle->setObjectName(QStringLiteral("cmbBorderStyle"));
        cmbBorderStyle->setIconSize(QSize(64, 16));

        gridLayout_4->addWidget(cmbBorderStyle, 1, 3, 1, 2);


        verticalLayout_5->addLayout(gridLayout_4);


        verticalLayout_4->addWidget(groupBox_41);

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
         << QApplication::translate("PageSettingDlg", "A3", 0)
         << QApplication::translate("PageSettingDlg", "A4", 0)
         << QApplication::translate("PageSettingDlg", "A5", 0)
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
        label_3->setText(QApplication::translate("PageSettingDlg", "cm", 0));
        label_4->setText(QApplication::translate("PageSettingDlg", "cm", 0));
        label_5->setText(QApplication::translate("PageSettingDlg", "Left", 0));
        label_7->setText(QApplication::translate("PageSettingDlg", "Right", 0));
        label_8->setText(QApplication::translate("PageSettingDlg", "Bottom", 0));
        label->setText(QApplication::translate("PageSettingDlg", "cm", 0));
        label_2->setText(QApplication::translate("PageSettingDlg", "cm", 0));
        label_6->setText(QApplication::translate("PageSettingDlg", "Top", 0));
        groupBox_41->setTitle(QApplication::translate("PageSettingDlg", "Page's border", 0));
        chkDrawBorder->setText(QApplication::translate("PageSettingDlg", "Draw border", 0));
        label_14->setText(QApplication::translate("PageSettingDlg", "Border color", 0));
        lblBorderColor->setText(QString());
        btnBorderColor->setText(QApplication::translate("PageSettingDlg", "...", 0));
        label_9->setText(QApplication::translate("PageSettingDlg", "Border width", 0));
        label_15->setText(QApplication::translate("PageSettingDlg", "Border style", 0));
        btnOK->setText(QApplication::translate("PageSettingDlg", "OK", 0));
        btnCancel->setText(QApplication::translate("PageSettingDlg", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class PageSettingDlg: public Ui_PageSettingDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGESETTINGDLG_H
