/********************************************************************************
** Form generated from reading UI file 'ItemPropertyDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITEMPROPERTYDLG_H
#define UI_ITEMPROPERTYDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ItemPropertyDlg
{
public:
    QVBoxLayout *verticalLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QTableWidget *tableWidget;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLineEdit *edtParentTable;
    QComboBox *parentColumn;
    QLabel *label_3;
    QComboBox *childColumn;
    QLabel *label_4;
    QLineEdit *edtChildTable;
    QLabel *label_5;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOK;
    QPushButton *btnClose;

    void setupUi(QDialog *ItemPropertyDlg)
    {
        if (ItemPropertyDlg->objectName().isEmpty())
            ItemPropertyDlg->setObjectName(QStringLiteral("ItemPropertyDlg"));
        ItemPropertyDlg->resize(432, 259);
        verticalLayout_2 = new QVBoxLayout(ItemPropertyDlg);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        stackedWidget = new QStackedWidget(ItemPropertyDlg);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        verticalLayout = new QVBoxLayout(page);
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(page);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(page);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        tableWidget = new QTableWidget(page);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setAlternatingRowColors(true);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(20);
        tableWidget->verticalHeader()->setStretchLastSection(false);

        verticalLayout->addWidget(tableWidget);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        verticalLayout_3 = new QVBoxLayout(page_2);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(page_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        edtParentTable = new QLineEdit(groupBox);
        edtParentTable->setObjectName(QStringLiteral("edtParentTable"));
        edtParentTable->setReadOnly(true);

        gridLayout->addWidget(edtParentTable, 0, 5, 1, 1);

        parentColumn = new QComboBox(groupBox);
        parentColumn->setObjectName(QStringLiteral("parentColumn"));
        parentColumn->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        parentColumn->setMinimumContentsLength(15);

        gridLayout->addWidget(parentColumn, 1, 4, 1, 2);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 3, 1, 2);

        childColumn = new QComboBox(groupBox);
        childColumn->setObjectName(QStringLiteral("childColumn"));
        childColumn->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        childColumn->setMinimumContentsLength(15);

        gridLayout->addWidget(childColumn, 1, 1, 1, 2);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        edtChildTable = new QLineEdit(groupBox);
        edtChildTable->setObjectName(QStringLiteral("edtChildTable"));
        edtChildTable->setReadOnly(true);

        gridLayout->addWidget(edtChildTable, 0, 2, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 1, 3, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 3, 1, 1);


        verticalLayout_3->addWidget(groupBox);

        stackedWidget->addWidget(page_2);

        verticalLayout_2->addWidget(stackedWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnOK = new QPushButton(ItemPropertyDlg);
        btnOK->setObjectName(QStringLiteral("btnOK"));

        horizontalLayout->addWidget(btnOK);

        btnClose = new QPushButton(ItemPropertyDlg);
        btnClose->setObjectName(QStringLiteral("btnClose"));

        horizontalLayout->addWidget(btnClose);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(ItemPropertyDlg);
        QObject::connect(btnClose, SIGNAL(clicked()), ItemPropertyDlg, SLOT(close()));
        QObject::connect(btnOK, SIGNAL(clicked()), ItemPropertyDlg, SLOT(accept()));

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ItemPropertyDlg);
    } // setupUi

    void retranslateUi(QDialog *ItemPropertyDlg)
    {
        ItemPropertyDlg->setWindowTitle(QApplication::translate("ItemPropertyDlg", "Object property", 0));
        label->setText(QApplication::translate("ItemPropertyDlg", "Name", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ItemPropertyDlg", "Name", 0));
        groupBox->setTitle(QApplication::translate("ItemPropertyDlg", "Relation property", 0));
        label_3->setText(QApplication::translate("ItemPropertyDlg", "Parent table", 0));
        label_4->setText(QApplication::translate("ItemPropertyDlg", "Columns:", 0));
        label_5->setText(QApplication::translate("ItemPropertyDlg", "reference", 0));
        label_2->setText(QApplication::translate("ItemPropertyDlg", "Child table", 0));
        btnOK->setText(QApplication::translate("ItemPropertyDlg", "OK", 0));
        btnClose->setText(QApplication::translate("ItemPropertyDlg", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class ItemPropertyDlg: public Ui_ItemPropertyDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ITEMPROPERTYDLG_H
