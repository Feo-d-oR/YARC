/********************************************************************************
** Form generated from reading UI file 'RepScrollArea.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPSCROLLAREA_H
#define UI_REPSCROLLAREA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RepScrollArea
{
public:
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *verticalLayout_10;
    QSpacerItem *leftMarginsSpacer;
    QWidget *horRuler;
    QHBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_52;
    QSpacerItem *topMarginsSpacer;
    QWidget *verRuler;
    QVBoxLayout *nn;
    QWidget *repWidget;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QScrollArea *RepScrollArea)
    {
        if (RepScrollArea->objectName().isEmpty())
            RepScrollArea->setObjectName(QStringLiteral("RepScrollArea"));
        RepScrollArea->resize(982, 1323);
        RepScrollArea->setWindowTitle(QStringLiteral("ScrollArea"));
        RepScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 980, 1321));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout_10 = new QHBoxLayout();
        verticalLayout_10->setSpacing(0);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        leftMarginsSpacer = new QSpacerItem(26, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        verticalLayout_10->addItem(leftMarginsSpacer);

        horRuler = new QWidget(scrollAreaWidgetContents);
        horRuler->setObjectName(QStringLiteral("horRuler"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(horRuler->sizePolicy().hasHeightForWidth());
        horRuler->setSizePolicy(sizePolicy);
        horRuler->setMinimumSize(QSize(840, 20));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        horRuler->setPalette(palette);
        horRuler->setAutoFillBackground(true);

        verticalLayout_10->addWidget(horRuler);


        verticalLayout->addLayout(verticalLayout_10);

        verticalLayout_5 = new QHBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_52 = new QVBoxLayout();
        verticalLayout_52->setSpacing(0);
        verticalLayout_52->setObjectName(QStringLiteral("verticalLayout_52"));
        topMarginsSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_52->addItem(topMarginsSpacer);

        verRuler = new QWidget(scrollAreaWidgetContents);
        verRuler->setObjectName(QStringLiteral("verRuler"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(verRuler->sizePolicy().hasHeightForWidth());
        verRuler->setSizePolicy(sizePolicy1);
        verRuler->setMinimumSize(QSize(20, 1188));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush);
        verRuler->setPalette(palette1);
        verRuler->setAutoFillBackground(true);

        verticalLayout_52->addWidget(verRuler);


        verticalLayout_5->addLayout(verticalLayout_52);

        nn = new QVBoxLayout();
        nn->setObjectName(QStringLiteral("nn"));
        nn->setContentsMargins(0, -1, -1, -1);
        repWidget = new QWidget(scrollAreaWidgetContents);
        repWidget->setObjectName(QStringLiteral("repWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(repWidget->sizePolicy().hasHeightForWidth());
        repWidget->setSizePolicy(sizePolicy2);
        repWidget->setMinimumSize(QSize(840, 1188));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Base, brush);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush);
        repWidget->setPalette(palette2);
        repWidget->setAutoFillBackground(true);

        nn->addWidget(repWidget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        nn->addItem(verticalSpacer);


        verticalLayout_5->addLayout(nn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(verticalLayout_5);

        RepScrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(RepScrollArea);

        QMetaObject::connectSlotsByName(RepScrollArea);
    } // setupUi

    void retranslateUi(QScrollArea *RepScrollArea)
    {
        Q_UNUSED(RepScrollArea);
    } // retranslateUi

};

namespace Ui {
    class RepScrollArea: public Ui_RepScrollArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPSCROLLAREA_H
