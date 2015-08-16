/********************************************************************************
** Form generated from reading UI file 'updatedlg.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATEDLG_H
#define UI_UPDATEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UpdateDlg
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QProgressBar *pb1;
    QProgressBar *pb2;
    QLabel *lblInfo;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnUpdate;
    QPushButton *btnCancel;

    void setupUi(QDialog *UpdateDlg)
    {
        if (UpdateDlg->objectName().isEmpty())
            UpdateDlg->setObjectName(QStringLiteral("UpdateDlg"));
        UpdateDlg->resize(400, 325);
        verticalLayout = new QVBoxLayout(UpdateDlg);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableWidget = new QTableWidget(UpdateDlg);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(25);

        verticalLayout->addWidget(tableWidget);

        pb1 = new QProgressBar(UpdateDlg);
        pb1->setObjectName(QStringLiteral("pb1"));
        pb1->setValue(24);

        verticalLayout->addWidget(pb1);

        pb2 = new QProgressBar(UpdateDlg);
        pb2->setObjectName(QStringLiteral("pb2"));
        pb2->setValue(24);

        verticalLayout->addWidget(pb2);

        lblInfo = new QLabel(UpdateDlg);
        lblInfo->setObjectName(QStringLiteral("lblInfo"));

        verticalLayout->addWidget(lblInfo);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnUpdate = new QPushButton(UpdateDlg);
        btnUpdate->setObjectName(QStringLiteral("btnUpdate"));

        horizontalLayout->addWidget(btnUpdate);

        btnCancel = new QPushButton(UpdateDlg);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));

        horizontalLayout->addWidget(btnCancel);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(UpdateDlg);
        QObject::connect(btnCancel, SIGNAL(clicked()), UpdateDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(UpdateDlg);
    } // setupUi

    void retranslateUi(QDialog *UpdateDlg)
    {
        UpdateDlg->setWindowTitle(QApplication::translate("UpdateDlg", "Updating", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("UpdateDlg", "Progress", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("UpdateDlg", "Updating", 0));
        lblInfo->setText(QString());
        btnUpdate->setText(QApplication::translate("UpdateDlg", "Update", 0));
        btnCancel->setText(QApplication::translate("UpdateDlg", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class UpdateDlg: public Ui_UpdateDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATEDLG_H
