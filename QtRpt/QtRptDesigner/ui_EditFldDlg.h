/********************************************************************************
** Form generated from reading UI file 'EditFldDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITFLDDLG_H
#define UI_EDITFLDDLG_H

#include <Barcode.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qtexteditex.h>

QT_BEGIN_NAMESPACE

class Ui_EditFldDlg
{
public:
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_5;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *btnAddVariable;
    QToolButton *btnAddFunction;
    QToolButton *btnFormatting;
    QToolButton *btnTextDirection;
    QCheckBox *chkImage;
    QSpacerItem *horizontalSpacer_3;
    QTextEdit *textEdit;
    QLabel *lblAttention;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_6;
    QRadioButton *rdPrinting;
    QRadioButton *rdHighlighting;
    QGroupBox *grpCondition;
    QVBoxLayout *verticalLayout_6;
    QLineEdit *edtCondition;
    QHBoxLayout *horizontalLayout_7;
    QGroupBox *grpFont;
    QVBoxLayout *verticalLayout_7;
    QCheckBox *chkBold;
    QCheckBox *chkItalic;
    QCheckBox *chkUnderline;
    QCheckBox *chkStrikeout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lblColorF;
    QPushButton *btnColorF;
    QGroupBox *grpBackground;
    QVBoxLayout *verticalLayout_8;
    QRadioButton *rdTransparent;
    QRadioButton *rdOther;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *lblColorB;
    QPushButton *btnColorB;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *btnLoadImage;
    QCheckBox *chkIgnoreAspectRatio;
    QSpacerItem *horizontalSpacer_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QWidget *page_3;
    QVBoxLayout *verticalLayout_11;
    QTabWidget *tabDiagram;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_13;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_2;
    QLineEdit *edtCaption;
    QCheckBox *chkShowCaption;
    QCheckBox *chkShowGrid;
    QCheckBox *chkShowLegend;
    QCheckBox *chkGraphs;
    QCheckBox *chkGraphsCaption;
    QGroupBox *grpGraphCaption;
    QVBoxLayout *verticalLayout_10;
    QRadioButton *rbRealValue;
    QRadioButton *rbPercentValue;
    QSpacerItem *verticalSpacer_3;
    QWidget *tabGraphs;
    QVBoxLayout *verticalLayout_14;
    QHBoxLayout *horizontalLayout_9;
    QToolButton *btnAddRow;
    QToolButton *btnRemoveRow;
    QToolButton *btnUp;
    QToolButton *btnDown;
    QSpacerItem *horizontalSpacer_4;
    QTableWidget *tableWidget;
    QWidget *page_4;
    QGridLayout *gridLayout;
    BarCode *wBarcode;
    QLabel *label_4;
    QComboBox *bstyle;
    QLabel *label_5;
    QComboBox *cbFrameType;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_3;
    QLineEdit *edtValue;
    QWidget *page_5;
    QVBoxLayout *verticalLayout_15;
    QTextEditEx *textEditRich;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOK;
    QPushButton *btnCancel;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *EditFldDlg)
    {
        if (EditFldDlg->objectName().isEmpty())
            EditFldDlg->setObjectName(QStringLiteral("EditFldDlg"));
        EditFldDlg->resize(521, 364);
        verticalLayout = new QVBoxLayout(EditFldDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        stackedWidget = new QStackedWidget(EditFldDlg);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        verticalLayout_2 = new QVBoxLayout(page);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(page);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_5 = new QVBoxLayout(tab);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 2, 0, 0);
        widget_2 = new QWidget(tab);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 3);
        btnAddVariable = new QToolButton(widget_2);
        btnAddVariable->setObjectName(QStringLiteral("btnAddVariable"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/images/variable.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnAddVariable->setIcon(icon);
        btnAddVariable->setAutoRaise(true);

        horizontalLayout_3->addWidget(btnAddVariable);

        btnAddFunction = new QToolButton(widget_2);
        btnAddFunction->setObjectName(QStringLiteral("btnAddFunction"));
        btnAddFunction->setEnabled(true);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/prefix1/images/function.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnAddFunction->setIcon(icon1);
        btnAddFunction->setAutoRaise(true);

        horizontalLayout_3->addWidget(btnAddFunction);

        btnFormatting = new QToolButton(widget_2);
        btnFormatting->setObjectName(QStringLiteral("btnFormatting"));
        btnFormatting->setEnabled(true);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/new/prefix1/images/formating.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnFormatting->setIcon(icon2);
        btnFormatting->setAutoRaise(true);

        horizontalLayout_3->addWidget(btnFormatting);

        btnTextDirection = new QToolButton(widget_2);
        btnTextDirection->setObjectName(QStringLiteral("btnTextDirection"));
        btnTextDirection->setEnabled(false);
        btnTextDirection->setCheckable(true);
        btnTextDirection->setAutoRaise(true);

        horizontalLayout_3->addWidget(btnTextDirection);

        chkImage = new QCheckBox(widget_2);
        chkImage->setObjectName(QStringLiteral("chkImage"));

        horizontalLayout_3->addWidget(chkImage);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_5->addWidget(widget_2);

        textEdit = new QTextEdit(tab);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        verticalLayout_5->addWidget(textEdit);

        lblAttention = new QLabel(tab);
        lblAttention->setObjectName(QStringLiteral("lblAttention"));
        lblAttention->setStyleSheet(QStringLiteral("border-color: rgb(255, 255, 255);"));

        verticalLayout_5->addWidget(lblAttention);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_9 = new QVBoxLayout(tab_2);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        rdPrinting = new QRadioButton(tab_2);
        buttonGroup = new QButtonGroup(EditFldDlg);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(rdPrinting);
        rdPrinting->setObjectName(QStringLiteral("rdPrinting"));
        rdPrinting->setChecked(true);

        horizontalLayout_6->addWidget(rdPrinting);

        rdHighlighting = new QRadioButton(tab_2);
        buttonGroup->addButton(rdHighlighting);
        rdHighlighting->setObjectName(QStringLiteral("rdHighlighting"));

        horizontalLayout_6->addWidget(rdHighlighting);


        verticalLayout_9->addLayout(horizontalLayout_6);

        grpCondition = new QGroupBox(tab_2);
        grpCondition->setObjectName(QStringLiteral("grpCondition"));
        verticalLayout_6 = new QVBoxLayout(grpCondition);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        edtCondition = new QLineEdit(grpCondition);
        edtCondition->setObjectName(QStringLiteral("edtCondition"));

        verticalLayout_6->addWidget(edtCondition);


        verticalLayout_9->addWidget(grpCondition);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        grpFont = new QGroupBox(tab_2);
        grpFont->setObjectName(QStringLiteral("grpFont"));
        grpFont->setEnabled(false);
        verticalLayout_7 = new QVBoxLayout(grpFont);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        chkBold = new QCheckBox(grpFont);
        chkBold->setObjectName(QStringLiteral("chkBold"));

        verticalLayout_7->addWidget(chkBold);

        chkItalic = new QCheckBox(grpFont);
        chkItalic->setObjectName(QStringLiteral("chkItalic"));

        verticalLayout_7->addWidget(chkItalic);

        chkUnderline = new QCheckBox(grpFont);
        chkUnderline->setObjectName(QStringLiteral("chkUnderline"));

        verticalLayout_7->addWidget(chkUnderline);

        chkStrikeout = new QCheckBox(grpFont);
        chkStrikeout->setObjectName(QStringLiteral("chkStrikeout"));

        verticalLayout_7->addWidget(chkStrikeout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        lblColorF = new QLabel(grpFont);
        lblColorF->setObjectName(QStringLiteral("lblColorF"));
        lblColorF->setFrameShape(QFrame::Box);
        lblColorF->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(lblColorF);

        btnColorF = new QPushButton(grpFont);
        btnColorF->setObjectName(QStringLiteral("btnColorF"));

        horizontalLayout_4->addWidget(btnColorF);


        verticalLayout_7->addLayout(horizontalLayout_4);


        horizontalLayout_7->addWidget(grpFont);

        grpBackground = new QGroupBox(tab_2);
        grpBackground->setObjectName(QStringLiteral("grpBackground"));
        grpBackground->setEnabled(false);
        verticalLayout_8 = new QVBoxLayout(grpBackground);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        rdTransparent = new QRadioButton(grpBackground);
        rdTransparent->setObjectName(QStringLiteral("rdTransparent"));
        rdTransparent->setChecked(true);

        verticalLayout_8->addWidget(rdTransparent);

        rdOther = new QRadioButton(grpBackground);
        rdOther->setObjectName(QStringLiteral("rdOther"));

        verticalLayout_8->addWidget(rdOther);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        lblColorB = new QLabel(grpBackground);
        lblColorB->setObjectName(QStringLiteral("lblColorB"));
        lblColorB->setFrameShape(QFrame::Box);
        lblColorB->setFrameShadow(QFrame::Sunken);

        horizontalLayout_5->addWidget(lblColorB);

        btnColorB = new QPushButton(grpBackground);
        btnColorB->setObjectName(QStringLiteral("btnColorB"));

        horizontalLayout_5->addWidget(btnColorB);


        verticalLayout_8->addLayout(horizontalLayout_5);


        horizontalLayout_7->addWidget(grpBackground);


        verticalLayout_9->addLayout(horizontalLayout_7);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_2->addWidget(tabWidget);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        verticalLayout_3 = new QVBoxLayout(page_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(page_2);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        btnLoadImage = new QToolButton(widget);
        btnLoadImage->setObjectName(QStringLiteral("btnLoadImage"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/new/prefix1/images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnLoadImage->setIcon(icon3);
        btnLoadImage->setAutoRaise(true);

        horizontalLayout_2->addWidget(btnLoadImage);

        chkIgnoreAspectRatio = new QCheckBox(widget);
        chkIgnoreAspectRatio->setObjectName(QStringLiteral("chkIgnoreAspectRatio"));

        horizontalLayout_2->addWidget(chkIgnoreAspectRatio);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_3->addWidget(widget);

        scrollArea = new QScrollArea(page_2);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 98, 28));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/picture.png")));

        verticalLayout_4->addWidget(label);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_3->addWidget(scrollArea);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        verticalLayout_11 = new QVBoxLayout(page_3);
        verticalLayout_11->setSpacing(0);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        tabDiagram = new QTabWidget(page_3);
        tabDiagram->setObjectName(QStringLiteral("tabDiagram"));
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        verticalLayout_13 = new QVBoxLayout(tab_5);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        groupBox = new QGroupBox(tab_5);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_12 = new QVBoxLayout(groupBox);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_8->addWidget(label_2);

        edtCaption = new QLineEdit(groupBox);
        edtCaption->setObjectName(QStringLiteral("edtCaption"));

        horizontalLayout_8->addWidget(edtCaption);


        verticalLayout_12->addLayout(horizontalLayout_8);

        chkShowCaption = new QCheckBox(groupBox);
        chkShowCaption->setObjectName(QStringLiteral("chkShowCaption"));

        verticalLayout_12->addWidget(chkShowCaption);

        chkShowGrid = new QCheckBox(groupBox);
        chkShowGrid->setObjectName(QStringLiteral("chkShowGrid"));

        verticalLayout_12->addWidget(chkShowGrid);

        chkShowLegend = new QCheckBox(groupBox);
        chkShowLegend->setObjectName(QStringLiteral("chkShowLegend"));

        verticalLayout_12->addWidget(chkShowLegend);

        chkGraphs = new QCheckBox(groupBox);
        chkGraphs->setObjectName(QStringLiteral("chkGraphs"));

        verticalLayout_12->addWidget(chkGraphs);

        chkGraphsCaption = new QCheckBox(groupBox);
        chkGraphsCaption->setObjectName(QStringLiteral("chkGraphsCaption"));

        verticalLayout_12->addWidget(chkGraphsCaption);

        grpGraphCaption = new QGroupBox(groupBox);
        grpGraphCaption->setObjectName(QStringLiteral("grpGraphCaption"));
        grpGraphCaption->setEnabled(false);
        verticalLayout_10 = new QVBoxLayout(grpGraphCaption);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        rbRealValue = new QRadioButton(grpGraphCaption);
        rbRealValue->setObjectName(QStringLiteral("rbRealValue"));
        rbRealValue->setChecked(true);

        verticalLayout_10->addWidget(rbRealValue);

        rbPercentValue = new QRadioButton(grpGraphCaption);
        rbPercentValue->setObjectName(QStringLiteral("rbPercentValue"));

        verticalLayout_10->addWidget(rbPercentValue);


        verticalLayout_12->addWidget(grpGraphCaption);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_12->addItem(verticalSpacer_3);


        verticalLayout_13->addWidget(groupBox);

        tabDiagram->addTab(tab_5, QString());
        tabGraphs = new QWidget();
        tabGraphs->setObjectName(QStringLiteral("tabGraphs"));
        verticalLayout_14 = new QVBoxLayout(tabGraphs);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(0);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        btnAddRow = new QToolButton(tabGraphs);
        btnAddRow->setObjectName(QStringLiteral("btnAddRow"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/new/prefix1/images/edit_add.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnAddRow->setIcon(icon4);

        horizontalLayout_9->addWidget(btnAddRow);

        btnRemoveRow = new QToolButton(tabGraphs);
        btnRemoveRow->setObjectName(QStringLiteral("btnRemoveRow"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/new/prefix1/images/edit_remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnRemoveRow->setIcon(icon5);

        horizontalLayout_9->addWidget(btnRemoveRow);

        btnUp = new QToolButton(tabGraphs);
        btnUp->setObjectName(QStringLiteral("btnUp"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/new/prefix1/images/up.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnUp->setIcon(icon6);

        horizontalLayout_9->addWidget(btnUp);

        btnDown = new QToolButton(tabGraphs);
        btnDown->setObjectName(QStringLiteral("btnDown"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/new/prefix1/images/down.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnDown->setIcon(icon7);

        horizontalLayout_9->addWidget(btnDown);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_4);


        verticalLayout_14->addLayout(horizontalLayout_9);

        tableWidget = new QTableWidget(tabGraphs);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setColumnCount(3);
        tableWidget->horizontalHeader()->setDefaultSectionSize(120);
        tableWidget->horizontalHeader()->setMinimumSectionSize(30);
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(22);

        verticalLayout_14->addWidget(tableWidget);

        tabDiagram->addTab(tabGraphs, QString());

        verticalLayout_11->addWidget(tabDiagram);

        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        gridLayout = new QGridLayout(page_4);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        wBarcode = new BarCode(page_4);
        wBarcode->setObjectName(QStringLiteral("wBarcode"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(wBarcode->sizePolicy().hasHeightForWidth());
        wBarcode->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(wBarcode, 0, 0, 1, 4);

        label_4 = new QLabel(page_4);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        bstyle = new QComboBox(page_4);
        bstyle->setObjectName(QStringLiteral("bstyle"));

        gridLayout->addWidget(bstyle, 1, 1, 1, 1);

        label_5 = new QLabel(page_4);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 1, 2, 1, 1);

        cbFrameType = new QComboBox(page_4);
        cbFrameType->setObjectName(QStringLiteral("cbFrameType"));

        gridLayout->addWidget(cbFrameType, 1, 3, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_3 = new QLabel(page_4);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_10->addWidget(label_3);

        edtValue = new QLineEdit(page_4);
        edtValue->setObjectName(QStringLiteral("edtValue"));

        horizontalLayout_10->addWidget(edtValue);


        gridLayout->addLayout(horizontalLayout_10, 2, 0, 1, 4);

        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName(QStringLiteral("page_5"));
        verticalLayout_15 = new QVBoxLayout(page_5);
        verticalLayout_15->setSpacing(0);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        verticalLayout_15->setContentsMargins(0, 0, 0, 0);
        textEditRich = new QTextEditEx(page_5);
        textEditRich->setObjectName(QStringLiteral("textEditRich"));

        verticalLayout_15->addWidget(textEditRich);

        stackedWidget->addWidget(page_5);

        verticalLayout->addWidget(stackedWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnOK = new QPushButton(EditFldDlg);
        btnOK->setObjectName(QStringLiteral("btnOK"));

        horizontalLayout->addWidget(btnOK);

        btnCancel = new QPushButton(EditFldDlg);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));

        horizontalLayout->addWidget(btnCancel);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(EditFldDlg);
        QObject::connect(btnOK, SIGNAL(clicked()), EditFldDlg, SLOT(accept()));
        QObject::connect(btnCancel, SIGNAL(clicked()), EditFldDlg, SLOT(reject()));
        QObject::connect(chkImage, SIGNAL(clicked(bool)), lblAttention, SLOT(setVisible(bool)));
        QObject::connect(chkGraphsCaption, SIGNAL(toggled(bool)), grpGraphCaption, SLOT(setEnabled(bool)));

        stackedWidget->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);
        tabDiagram->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EditFldDlg);
    } // setupUi

    void retranslateUi(QDialog *EditFldDlg)
    {
        EditFldDlg->setWindowTitle(QApplication::translate("EditFldDlg", "Field editor", 0));
#ifndef QT_NO_TOOLTIP
        btnAddVariable->setToolTip(QApplication::translate("EditFldDlg", "Add variable", 0));
#endif // QT_NO_TOOLTIP
        btnAddVariable->setText(QApplication::translate("EditFldDlg", "...", 0));
#ifndef QT_NO_TOOLTIP
        btnAddFunction->setToolTip(QApplication::translate("EditFldDlg", "Add function", 0));
#endif // QT_NO_TOOLTIP
        btnAddFunction->setText(QApplication::translate("EditFldDlg", "...", 0));
#ifndef QT_NO_TOOLTIP
        btnFormatting->setToolTip(QApplication::translate("EditFldDlg", "Add formatting", 0));
#endif // QT_NO_TOOLTIP
        btnFormatting->setText(QApplication::translate("EditFldDlg", "...", 0));
#ifndef QT_NO_TOOLTIP
        btnTextDirection->setToolTip(QApplication::translate("EditFldDlg", "Text direction", 0));
#endif // QT_NO_TOOLTIP
        btnTextDirection->setText(QApplication::translate("EditFldDlg", "<-", 0));
        chkImage->setText(QApplication::translate("EditFldDlg", "Proccess as Image", 0));
        lblAttention->setText(QApplication::translate("EditFldDlg", "Attention! You may enter just ONE varibale and not any text.", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("EditFldDlg", "Text", 0));
        rdPrinting->setText(QApplication::translate("EditFldDlg", "Printing", 0));
        rdHighlighting->setText(QApplication::translate("EditFldDlg", "Hightlighting", 0));
        grpCondition->setTitle(QApplication::translate("EditFldDlg", "Condition", 0));
        grpFont->setTitle(QApplication::translate("EditFldDlg", "Font", 0));
        chkBold->setText(QApplication::translate("EditFldDlg", "Bold", 0));
        chkItalic->setText(QApplication::translate("EditFldDlg", "Italic", 0));
        chkUnderline->setText(QApplication::translate("EditFldDlg", "Underline", 0));
        chkStrikeout->setText(QApplication::translate("EditFldDlg", "Strikeout", 0));
        lblColorF->setText(QString());
        btnColorF->setText(QApplication::translate("EditFldDlg", "Color...", 0));
        grpBackground->setTitle(QApplication::translate("EditFldDlg", "Background", 0));
        rdTransparent->setText(QApplication::translate("EditFldDlg", "Transparent", 0));
        rdOther->setText(QApplication::translate("EditFldDlg", "Other", 0));
        lblColorB->setText(QString());
        btnColorB->setText(QApplication::translate("EditFldDlg", "Color...", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("EditFldDlg", "Condtion", 0));
        btnLoadImage->setText(QApplication::translate("EditFldDlg", "...", 0));
        chkIgnoreAspectRatio->setText(QApplication::translate("EditFldDlg", "Ignore aspect ratio", 0));
        label->setText(QString());
        groupBox->setTitle(QApplication::translate("EditFldDlg", "Diagram", 0));
        label_2->setText(QApplication::translate("EditFldDlg", "Chart's caption", 0));
        chkShowCaption->setText(QApplication::translate("EditFldDlg", "Show caption", 0));
        chkShowGrid->setText(QApplication::translate("EditFldDlg", "Show grid", 0));
        chkShowLegend->setText(QApplication::translate("EditFldDlg", "Show legend", 0));
        chkGraphs->setText(QApplication::translate("EditFldDlg", "Set the params of the graphs", 0));
        chkGraphsCaption->setText(QApplication::translate("EditFldDlg", "Show graph's caption", 0));
        grpGraphCaption->setTitle(QApplication::translate("EditFldDlg", "Graph's caption", 0));
        rbRealValue->setText(QApplication::translate("EditFldDlg", "Real values", 0));
        rbPercentValue->setText(QApplication::translate("EditFldDlg", "Percent values", 0));
        tabDiagram->setTabText(tabDiagram->indexOf(tab_5), QApplication::translate("EditFldDlg", "Diagram's property", 0));
#ifndef QT_NO_TOOLTIP
        btnAddRow->setToolTip(QApplication::translate("EditFldDlg", "Add row", 0));
#endif // QT_NO_TOOLTIP
        btnAddRow->setText(QApplication::translate("EditFldDlg", "...", 0));
#ifndef QT_NO_TOOLTIP
        btnRemoveRow->setToolTip(QApplication::translate("EditFldDlg", "Remove row", 0));
#endif // QT_NO_TOOLTIP
        btnRemoveRow->setText(QApplication::translate("EditFldDlg", "...", 0));
#ifndef QT_NO_TOOLTIP
        btnUp->setToolTip(QApplication::translate("EditFldDlg", "Up", 0));
#endif // QT_NO_TOOLTIP
        btnUp->setText(QApplication::translate("EditFldDlg", "...", 0));
#ifndef QT_NO_TOOLTIP
        btnDown->setToolTip(QApplication::translate("EditFldDlg", "Down", 0));
#endif // QT_NO_TOOLTIP
        btnDown->setText(QApplication::translate("EditFldDlg", "...", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("EditFldDlg", "Caption", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("EditFldDlg", "Value", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("EditFldDlg", "Color", 0));
        tabDiagram->setTabText(tabDiagram->indexOf(tabGraphs), QApplication::translate("EditFldDlg", "Graphs", 0));
        label_4->setText(QApplication::translate("EditFldDlg", "Barcode type", 0));
        label_5->setText(QApplication::translate("EditFldDlg", "Frame type", 0));
        label_3->setText(QApplication::translate("EditFldDlg", "Value:", 0));
        btnOK->setText(QApplication::translate("EditFldDlg", "OK", 0));
        btnCancel->setText(QApplication::translate("EditFldDlg", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class EditFldDlg: public Ui_EditFldDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITFLDDLG_H
