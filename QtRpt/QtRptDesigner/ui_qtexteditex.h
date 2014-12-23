/********************************************************************************
** Form generated from reading UI file 'qtexteditex.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTEXTEDITEX_H
#define UI_QTEXTEDITEX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTextEditEx
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QToolButton *btnCut;
    QToolButton *btnCopy;
    QToolButton *btnPaste;
    QSpacerItem *horizontalSpacer_10;
    QToolButton *btnTextBold;
    QToolButton *btnTextItalic;
    QToolButton *btnUnderline;
    QSpacerItem *horizontalSpacer_4;
    QToolButton *btnAlignLeft;
    QToolButton *btnAlignCenter;
    QToolButton *btnAlignRight;
    QToolButton *btnAlignJustify;
    QSpacerItem *horizontalSpacer;
    QComboBox *comboStyle;
    QSpacerItem *horizontalSpacer_5;
    QToolButton *btnTextColor;
    QFontComboBox *comboFont;
    QComboBox *comboSize;
    QToolButton *btnTextDirection;
    QSpacerItem *horizontalSpacer_9;
    QTextEdit *textEdit;

    void setupUi(QWidget *QTextEditEx)
    {
        if (QTextEditEx->objectName().isEmpty())
            QTextEditEx->setObjectName(QStringLiteral("QTextEditEx"));
        QTextEditEx->resize(631, 383);
        QTextEditEx->setWindowTitle(QStringLiteral("Form"));
        verticalLayout = new QVBoxLayout(QTextEditEx);
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setSizeConstraint(QLayout::SetDefaultConstraint);
        btnCut = new QToolButton(QTextEditEx);
        btnCut->setObjectName(QStringLiteral("btnCut"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/images/cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnCut->setIcon(icon);
        btnCut->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnCut);

        btnCopy = new QToolButton(QTextEditEx);
        btnCopy->setObjectName(QStringLiteral("btnCopy"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/prefix1/images/copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnCopy->setIcon(icon1);
        btnCopy->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnCopy);

        btnPaste = new QToolButton(QTextEditEx);
        btnPaste->setObjectName(QStringLiteral("btnPaste"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/new/prefix1/images/paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPaste->setIcon(icon2);
        btnPaste->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnPaste);

        horizontalSpacer_10 = new QSpacerItem(10, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_10);

        btnTextBold = new QToolButton(QTextEditEx);
        btnTextBold->setObjectName(QStringLiteral("btnTextBold"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/new/prefix1/images/textbold.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnTextBold->setIcon(icon3);
        btnTextBold->setCheckable(true);
        btnTextBold->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnTextBold);

        btnTextItalic = new QToolButton(QTextEditEx);
        btnTextItalic->setObjectName(QStringLiteral("btnTextItalic"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/new/prefix1/images/textitalic.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnTextItalic->setIcon(icon4);
        btnTextItalic->setCheckable(true);
        btnTextItalic->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnTextItalic);

        btnUnderline = new QToolButton(QTextEditEx);
        btnUnderline->setObjectName(QStringLiteral("btnUnderline"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/new/prefix1/images/textunder.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnUnderline->setIcon(icon5);
        btnUnderline->setCheckable(true);
        btnUnderline->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnUnderline);

        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);

        btnAlignLeft = new QToolButton(QTextEditEx);
        btnAlignLeft->setObjectName(QStringLiteral("btnAlignLeft"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/new/prefix1/images/textleft.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnAlignLeft->setIcon(icon6);
        btnAlignLeft->setCheckable(true);
        btnAlignLeft->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnAlignLeft);

        btnAlignCenter = new QToolButton(QTextEditEx);
        btnAlignCenter->setObjectName(QStringLiteral("btnAlignCenter"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/new/prefix1/images/textcenter.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnAlignCenter->setIcon(icon7);
        btnAlignCenter->setCheckable(true);
        btnAlignCenter->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnAlignCenter);

        btnAlignRight = new QToolButton(QTextEditEx);
        btnAlignRight->setObjectName(QStringLiteral("btnAlignRight"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/new/prefix1/images/textright.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnAlignRight->setIcon(icon8);
        btnAlignRight->setCheckable(true);
        btnAlignRight->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnAlignRight);

        btnAlignJustify = new QToolButton(QTextEditEx);
        btnAlignJustify->setObjectName(QStringLiteral("btnAlignJustify"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/new/prefix1/images/textjustify.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnAlignJustify->setIcon(icon9);
        btnAlignJustify->setCheckable(true);
        btnAlignJustify->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnAlignJustify);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        comboStyle = new QComboBox(QTextEditEx);
        comboStyle->setObjectName(QStringLiteral("comboStyle"));

        horizontalLayout_6->addWidget(comboStyle);

        horizontalSpacer_5 = new QSpacerItem(10, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        btnTextColor = new QToolButton(QTextEditEx);
        btnTextColor->setObjectName(QStringLiteral("btnTextColor"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/new/prefix1/images/fontColor.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnTextColor->setIcon(icon10);
        btnTextColor->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnTextColor);

        comboFont = new QFontComboBox(QTextEditEx);
        comboFont->setObjectName(QStringLiteral("comboFont"));
        QFont font;
        comboFont->setCurrentFont(font);

        horizontalLayout_6->addWidget(comboFont);

        comboSize = new QComboBox(QTextEditEx);
        comboSize->insertItems(0, QStringList()
         << QStringLiteral("6")
         << QStringLiteral("7")
         << QStringLiteral("8")
         << QStringLiteral("9")
         << QStringLiteral("10")
         << QStringLiteral("11")
         << QStringLiteral("12")
         << QStringLiteral("14")
         << QStringLiteral("16")
         << QStringLiteral("18")
         << QStringLiteral("20")
         << QStringLiteral("22")
         << QStringLiteral("24")
         << QStringLiteral("26")
         << QStringLiteral("28")
         << QStringLiteral("36")
         << QStringLiteral("48")
         << QStringLiteral("72")
        );
        comboSize->setObjectName(QStringLiteral("comboSize"));
        comboSize->setEditable(true);
        comboSize->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_6->addWidget(comboSize);

        btnTextDirection = new QToolButton(QTextEditEx);
        btnTextDirection->setObjectName(QStringLiteral("btnTextDirection"));
        btnTextDirection->setCheckable(true);
        btnTextDirection->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnTextDirection);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_9);


        verticalLayout->addLayout(horizontalLayout_6);

        textEdit = new QTextEdit(QTextEditEx);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        verticalLayout->addWidget(textEdit);


        retranslateUi(QTextEditEx);

        comboSize->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QTextEditEx);
    } // setupUi

    void retranslateUi(QWidget *QTextEditEx)
    {
#ifndef QT_NO_TOOLTIP
        btnCut->setToolTip(QApplication::translate("QTextEditEx", "Cut", 0));
#endif // QT_NO_TOOLTIP
        btnCut->setText(QApplication::translate("QTextEditEx", "...", 0));
#ifndef QT_NO_TOOLTIP
        btnCopy->setToolTip(QApplication::translate("QTextEditEx", "Copy", 0));
#endif // QT_NO_TOOLTIP
        btnCopy->setText(QApplication::translate("QTextEditEx", "...", 0));
#ifndef QT_NO_TOOLTIP
        btnPaste->setToolTip(QApplication::translate("QTextEditEx", "Paste", 0));
#endif // QT_NO_TOOLTIP
        btnPaste->setText(QApplication::translate("QTextEditEx", "...", 0));
#ifndef QT_NO_TOOLTIP
        btnTextBold->setToolTip(QApplication::translate("QTextEditEx", "Bold", 0));
#endif // QT_NO_TOOLTIP
        btnTextBold->setText(QApplication::translate("QTextEditEx", "...", 0));
#ifndef QT_NO_TOOLTIP
        btnTextItalic->setToolTip(QApplication::translate("QTextEditEx", "Italic", 0));
#endif // QT_NO_TOOLTIP
        btnTextItalic->setText(QApplication::translate("QTextEditEx", "...", 0));
#ifndef QT_NO_TOOLTIP
        btnUnderline->setToolTip(QApplication::translate("QTextEditEx", "Underline", 0));
#endif // QT_NO_TOOLTIP
        btnUnderline->setText(QApplication::translate("QTextEditEx", "...", 0));
#ifndef QT_NO_TOOLTIP
        btnAlignLeft->setToolTip(QApplication::translate("QTextEditEx", "Align left", 0));
#endif // QT_NO_TOOLTIP
        btnAlignLeft->setText(QApplication::translate("QTextEditEx", "...", 0));
#ifndef QT_NO_TOOLTIP
        btnAlignCenter->setToolTip(QApplication::translate("QTextEditEx", "Align center", 0));
#endif // QT_NO_TOOLTIP
        btnAlignCenter->setText(QApplication::translate("QTextEditEx", "...", 0));
#ifndef QT_NO_TOOLTIP
        btnAlignRight->setToolTip(QApplication::translate("QTextEditEx", "Align right", 0));
#endif // QT_NO_TOOLTIP
        btnAlignRight->setText(QApplication::translate("QTextEditEx", "...", 0));
#ifndef QT_NO_TOOLTIP
        btnAlignJustify->setToolTip(QApplication::translate("QTextEditEx", "Align jusify", 0));
#endif // QT_NO_TOOLTIP
        btnAlignJustify->setText(QApplication::translate("QTextEditEx", "...", 0));
#ifndef QT_NO_TOOLTIP
        comboStyle->setToolTip(QApplication::translate("QTextEditEx", "List", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        btnTextColor->setToolTip(QApplication::translate("QTextEditEx", "Font color", 0));
#endif // QT_NO_TOOLTIP
        btnTextColor->setText(QApplication::translate("QTextEditEx", "...", 0));
#ifndef QT_NO_TOOLTIP
        comboFont->setToolTip(QApplication::translate("QTextEditEx", "Font", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        comboSize->setToolTip(QApplication::translate("QTextEditEx", "Font size", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        btnTextDirection->setToolTip(QApplication::translate("QTextEditEx", "TextDirection", 0));
#endif // QT_NO_TOOLTIP
        btnTextDirection->setText(QApplication::translate("QTextEditEx", "<-", 0));
        Q_UNUSED(QTextEditEx);
    } // retranslateUi

};

namespace Ui {
    class QTextEditEx: public Ui_QTextEditEx {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTEXTEDITEX_H
