/********************************************************************************
** Form generated from reading UI file 'FldPropertyDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLDPROPERTYDLG_H
#define UI_FLDPROPERTYDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FldPropertyDlg
{
public:
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_2;
    QTreeWidget *treeWidget;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *edtFiledGrouping;
    QCheckBox *chkStartLineNum;
    QCheckBox *chkStartNewPage;
    QSpacerItem *verticalSpacer;
    QWidget *page_3;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_5;
    QListWidget *lstCategory;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QListWidget *lstFormat;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QSpinBox *spnPrecision;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLineEdit *edtFornatString;
    QPushButton *btnClear;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOK;
    QPushButton *btnCancel;

    void setupUi(QDialog *FldPropertyDlg)
    {
        if (FldPropertyDlg->objectName().isEmpty())
            FldPropertyDlg->setObjectName(QStringLiteral("FldPropertyDlg"));
        FldPropertyDlg->resize(400, 300);
        verticalLayout = new QVBoxLayout(FldPropertyDlg);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        stackedWidget = new QStackedWidget(FldPropertyDlg);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        verticalLayout_2 = new QVBoxLayout(page);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        treeWidget = new QTreeWidget(page);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        treeWidget->setHeaderHidden(true);
        treeWidget->header()->setVisible(false);

        verticalLayout_2->addWidget(treeWidget);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        verticalLayout_3 = new QVBoxLayout(page_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(page_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        edtFiledGrouping = new QLineEdit(page_2);
        edtFiledGrouping->setObjectName(QStringLiteral("edtFiledGrouping"));

        horizontalLayout_2->addWidget(edtFiledGrouping);


        verticalLayout_3->addLayout(horizontalLayout_2);

        chkStartLineNum = new QCheckBox(page_2);
        chkStartLineNum->setObjectName(QStringLiteral("chkStartLineNum"));

        verticalLayout_3->addWidget(chkStartLineNum);

        chkStartNewPage = new QCheckBox(page_2);
        chkStartNewPage->setObjectName(QStringLiteral("chkStartNewPage"));
        chkStartNewPage->setEnabled(true);

        verticalLayout_3->addWidget(chkStartNewPage);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        verticalLayout_7 = new QVBoxLayout(page_3);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        groupBox = new QGroupBox(page_3);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_5 = new QVBoxLayout(groupBox);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        lstCategory = new QListWidget(groupBox);
        new QListWidgetItem(lstCategory);
        lstCategory->setObjectName(QStringLiteral("lstCategory"));

        verticalLayout_5->addWidget(lstCategory);


        horizontalLayout_4->addWidget(groupBox);

        groupBox_2 = new QGroupBox(page_3);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        lstFormat = new QListWidget(groupBox_2);
        lstFormat->setObjectName(QStringLiteral("lstFormat"));

        verticalLayout_4->addWidget(lstFormat);


        horizontalLayout_4->addWidget(groupBox_2);


        verticalLayout_7->addLayout(horizontalLayout_4);

        groupBox_3 = new QGroupBox(page_3);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_6 = new QVBoxLayout(groupBox_3);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        spnPrecision = new QSpinBox(groupBox_3);
        spnPrecision->setObjectName(QStringLiteral("spnPrecision"));
        spnPrecision->setMaximum(9);

        horizontalLayout_3->addWidget(spnPrecision);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_6->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_5->addWidget(label_3);

        edtFornatString = new QLineEdit(groupBox_3);
        edtFornatString->setObjectName(QStringLiteral("edtFornatString"));
        edtFornatString->setReadOnly(true);

        horizontalLayout_5->addWidget(edtFornatString);

        btnClear = new QPushButton(groupBox_3);
        btnClear->setObjectName(QStringLiteral("btnClear"));

        horizontalLayout_5->addWidget(btnClear);


        verticalLayout_6->addLayout(horizontalLayout_5);


        verticalLayout_7->addWidget(groupBox_3);

        stackedWidget->addWidget(page_3);

        verticalLayout->addWidget(stackedWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnOK = new QPushButton(FldPropertyDlg);
        btnOK->setObjectName(QStringLiteral("btnOK"));

        horizontalLayout->addWidget(btnOK);

        btnCancel = new QPushButton(FldPropertyDlg);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));

        horizontalLayout->addWidget(btnCancel);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(FldPropertyDlg);
        QObject::connect(btnCancel, SIGNAL(clicked()), FldPropertyDlg, SLOT(reject()));
        QObject::connect(btnOK, SIGNAL(clicked()), FldPropertyDlg, SLOT(accept()));
        QObject::connect(btnClear, SIGNAL(clicked()), edtFornatString, SLOT(clear()));
        QObject::connect(treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), FldPropertyDlg, SLOT(accept()));

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FldPropertyDlg);
    } // setupUi

    void retranslateUi(QDialog *FldPropertyDlg)
    {
        FldPropertyDlg->setWindowTitle(QApplication::translate("FldPropertyDlg", "Expression editor", 0));
        label->setText(QApplication::translate("FldPropertyDlg", "Data filed grouping", 0));
        chkStartLineNum->setText(QApplication::translate("FldPropertyDlg", "Start line numeration for each group", 0));
        chkStartNewPage->setText(QApplication::translate("FldPropertyDlg", "Start new page for each group", 0));
        groupBox->setTitle(QApplication::translate("FldPropertyDlg", "Category", 0));

        const bool __sortingEnabled = lstCategory->isSortingEnabled();
        lstCategory->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = lstCategory->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("FldPropertyDlg", "Number", 0));
        lstCategory->setSortingEnabled(__sortingEnabled);

        groupBox_2->setTitle(QApplication::translate("FldPropertyDlg", "Format", 0));
        groupBox_3->setTitle(QApplication::translate("FldPropertyDlg", "Other", 0));
        label_2->setText(QApplication::translate("FldPropertyDlg", "Precision", 0));
        label_3->setText(QApplication::translate("FldPropertyDlg", "Format string", 0));
        btnClear->setText(QApplication::translate("FldPropertyDlg", "Clear", 0));
        btnOK->setText(QApplication::translate("FldPropertyDlg", "OK", 0));
        btnCancel->setText(QApplication::translate("FldPropertyDlg", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class FldPropertyDlg: public Ui_FldPropertyDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLDPROPERTYDLG_H
