/********************************************************************************
** Form generated from reading UI file 'ReportBand.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPORTBAND_H
#define UI_REPORTBAND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "../CommonFiles/Qxyz_Label.h"

QT_BEGIN_NAMESPACE

class Ui_ReportBand
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QxyzLabel *lblBandType;
    QLabel *lblIcon;
    QSpacerItem *horizontalSpacer;
    QWidget *conWidget;

    void setupUi(QWidget *ReportBand)
    {
        if (ReportBand->objectName().isEmpty())
            ReportBand->setObjectName(QStringLiteral("ReportBand"));
        ReportBand->resize(673, 65);
        ReportBand->setContextMenuPolicy(Qt::ActionsContextMenu);
        ReportBand->setWindowTitle(QStringLiteral("Form"));
        verticalLayout = new QVBoxLayout(ReportBand);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(ReportBand);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Plain);
        frame->setLineWidth(0);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lblBandType = new QxyzLabel(frame);
        lblBandType->setObjectName(QStringLiteral("lblBandType"));
        sizePolicy.setHeightForWidth(lblBandType->sizePolicy().hasHeightForWidth());
        lblBandType->setSizePolicy(sizePolicy);
        lblBandType->setAutoFillBackground(false);
        lblBandType->setStyleSheet(QStringLiteral(""));
        lblBandType->setFrameShape(QFrame::NoFrame);
        lblBandType->setLineWidth(0);
        lblBandType->setText(QStringLiteral("TextLabel"));
        lblBandType->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lblBandType);

        lblIcon = new QLabel(frame);
        lblIcon->setObjectName(QStringLiteral("lblIcon"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblIcon->sizePolicy().hasHeightForWidth());
        lblIcon->setSizePolicy(sizePolicy1);
        lblIcon->setLineWidth(0);

        horizontalLayout->addWidget(lblIcon);

        horizontalSpacer = new QSpacerItem(5, 5, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(frame);

        conWidget = new QWidget(ReportBand);
        conWidget->setObjectName(QStringLiteral("conWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(conWidget->sizePolicy().hasHeightForWidth());
        conWidget->setSizePolicy(sizePolicy2);
        conWidget->setAcceptDrops(true);
        conWidget->setAutoFillBackground(false);
        conWidget->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(conWidget);


        retranslateUi(ReportBand);

        QMetaObject::connectSlotsByName(ReportBand);
    } // setupUi

    void retranslateUi(QWidget *ReportBand)
    {
        lblIcon->setText(QString());
        Q_UNUSED(ReportBand);
    } // retranslateUi

};

namespace Ui {
    class ReportBand: public Ui_ReportBand {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORTBAND_H
