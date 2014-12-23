/********************************************************************************
** Form generated from reading UI file 'SqlDesigner.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SQLDESIGNER_H
#define UI_SQLDESIGNER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SqlDesigner
{
public:
    QAction *actClearDiagram;
    QAction *actSelect;
    QAction *actRedo;
    QAction *actUndo;
    QAction *actAddRelationship;
    QAction *actDelete;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *rbCustom;
    QRadioButton *rbSql;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnClose;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLineEdit *edtHost;
    QLabel *label_2;
    QLineEdit *edtConnectionCoding;
    QLineEdit *edtDBName;
    QLineEdit *edtPassword;
    QLabel *label_9;
    QLineEdit *edtUserName;
    QLabel *label_6;
    QComboBox *cmbType;
    QPushButton *btnCheck;
    QLabel *label_7;
    QLabel *label_5;
    QLabel *label_8;
    QLabel *label_4;
    QLineEdit *edtCharsetCoding;
    QLabel *label_3;
    QLabel *label_11;
    QLabel *label_10;
    QLineEdit *edtConName;
    QLineEdit *edtPort;
    QHBoxLayout *horizontalLayout_3;
    QTreeWidget *treeWidget;
    QVBoxLayout *verticalLayout;
    QToolBar *widget;
    QGraphicsView *graphicsView;
    QLabel *label;
    QTextEdit *sqlEditor;

    void setupUi(QWidget *SqlDesigner)
    {
        if (SqlDesigner->objectName().isEmpty())
            SqlDesigner->setObjectName(QStringLiteral("SqlDesigner"));
        SqlDesigner->resize(500, 497);
        SqlDesigner->setMinimumSize(QSize(500, 0));
        SqlDesigner->setMaximumSize(QSize(500, 16777215));
        SqlDesigner->setWindowTitle(QStringLiteral(""));
        actClearDiagram = new QAction(SqlDesigner);
        actClearDiagram->setObjectName(QStringLiteral("actClearDiagram"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/images/document-new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actClearDiagram->setIcon(icon);
        actSelect = new QAction(SqlDesigner);
        actSelect->setObjectName(QStringLiteral("actSelect"));
        actSelect->setCheckable(true);
        actSelect->setChecked(true);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/prefix1/images/80-1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actSelect->setIcon(icon1);
        actRedo = new QAction(SqlDesigner);
        actRedo->setObjectName(QStringLiteral("actRedo"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/new/prefix1/images/edit-redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actRedo->setIcon(icon2);
        actUndo = new QAction(SqlDesigner);
        actUndo->setObjectName(QStringLiteral("actUndo"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/new/prefix1/images/edit-undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actUndo->setIcon(icon3);
        actAddRelationship = new QAction(SqlDesigner);
        actAddRelationship->setObjectName(QStringLiteral("actAddRelationship"));
        actAddRelationship->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/new/prefix1/images/item-relationship.png"), QSize(), QIcon::Normal, QIcon::Off);
        actAddRelationship->setIcon(icon4);
        actDelete = new QAction(SqlDesigner);
        actDelete->setObjectName(QStringLiteral("actDelete"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/new/prefix1/images/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        actDelete->setIcon(icon5);
        gridLayout = new QGridLayout(SqlDesigner);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        rbCustom = new QRadioButton(SqlDesigner);
        rbCustom->setObjectName(QStringLiteral("rbCustom"));
        rbCustom->setChecked(true);

        horizontalLayout_2->addWidget(rbCustom);

        rbSql = new QRadioButton(SqlDesigner);
        rbSql->setObjectName(QStringLiteral("rbSql"));

        horizontalLayout_2->addWidget(rbSql);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnClose = new QPushButton(SqlDesigner);
        btnClose->setObjectName(QStringLiteral("btnClose"));

        horizontalLayout->addWidget(btnClose);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);

        stackedWidget = new QStackedWidget(SqlDesigner);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        verticalLayout_2 = new QVBoxLayout(page_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(page_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        edtHost = new QLineEdit(groupBox);
        edtHost->setObjectName(QStringLiteral("edtHost"));

        gridLayout_2->addWidget(edtHost, 3, 2, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        edtConnectionCoding = new QLineEdit(groupBox);
        edtConnectionCoding->setObjectName(QStringLiteral("edtConnectionCoding"));

        gridLayout_2->addWidget(edtConnectionCoding, 1, 2, 1, 1);

        edtDBName = new QLineEdit(groupBox);
        edtDBName->setObjectName(QStringLiteral("edtDBName"));

        gridLayout_2->addWidget(edtDBName, 2, 2, 1, 1);

        edtPassword = new QLineEdit(groupBox);
        edtPassword->setObjectName(QStringLiteral("edtPassword"));

        gridLayout_2->addWidget(edtPassword, 3, 4, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 1, 3, 1, 1);

        edtUserName = new QLineEdit(groupBox);
        edtUserName->setObjectName(QStringLiteral("edtUserName"));

        gridLayout_2->addWidget(edtUserName, 2, 4, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 3, 3, 1, 1);

        cmbType = new QComboBox(groupBox);
        cmbType->setObjectName(QStringLiteral("cmbType"));

        gridLayout_2->addWidget(cmbType, 0, 1, 1, 2);

        btnCheck = new QPushButton(groupBox);
        btnCheck->setObjectName(QStringLiteral("btnCheck"));

        gridLayout_2->addWidget(btnCheck, 0, 4, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 0, 3, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 2, 3, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 1, 0, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 2);

        edtCharsetCoding = new QLineEdit(groupBox);
        edtCharsetCoding->setObjectName(QStringLiteral("edtCharsetCoding"));

        gridLayout_2->addWidget(edtCharsetCoding, 1, 4, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_2->addWidget(label_11, 4, 0, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_2->addWidget(label_10, 4, 3, 1, 1);

        edtConName = new QLineEdit(groupBox);
        edtConName->setObjectName(QStringLiteral("edtConName"));

        gridLayout_2->addWidget(edtConName, 4, 2, 1, 1);

        edtPort = new QLineEdit(groupBox);
        edtPort->setObjectName(QStringLiteral("edtPort"));

        gridLayout_2->addWidget(edtPort, 4, 4, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        treeWidget = new QTreeWidget(page_2);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setMaximumSize(QSize(110, 16777215));
        treeWidget->setDragEnabled(true);
        treeWidget->setDragDropMode(QAbstractItemView::DragOnly);
        treeWidget->setRootIsDecorated(false);
        treeWidget->header()->setVisible(false);

        horizontalLayout_3->addWidget(treeWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new QToolBar(page_2);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setIconSize(QSize(16, 16));
        widget->setFloatable(true);

        verticalLayout->addWidget(widget);

        graphicsView = new QGraphicsView(page_2);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        verticalLayout->addWidget(graphicsView);


        horizontalLayout_3->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_3);

        label = new QLabel(page_2);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_2->addWidget(label);

        sqlEditor = new QTextEdit(page_2);
        sqlEditor->setObjectName(QStringLiteral("sqlEditor"));
        sqlEditor->setMaximumSize(QSize(16777215, 100));

        verticalLayout_2->addWidget(sqlEditor);

        stackedWidget->addWidget(page_2);

        gridLayout->addWidget(stackedWidget, 1, 0, 1, 1);

        QWidget::setTabOrder(rbCustom, rbSql);
        QWidget::setTabOrder(rbSql, cmbType);
        QWidget::setTabOrder(cmbType, btnCheck);
        QWidget::setTabOrder(btnCheck, edtConnectionCoding);
        QWidget::setTabOrder(edtConnectionCoding, edtCharsetCoding);
        QWidget::setTabOrder(edtCharsetCoding, edtDBName);
        QWidget::setTabOrder(edtDBName, edtUserName);
        QWidget::setTabOrder(edtUserName, edtHost);
        QWidget::setTabOrder(edtHost, edtPassword);
        QWidget::setTabOrder(edtPassword, treeWidget);
        QWidget::setTabOrder(treeWidget, graphicsView);
        QWidget::setTabOrder(graphicsView, sqlEditor);
        QWidget::setTabOrder(sqlEditor, btnClose);

        widget->addAction(actClearDiagram);
        widget->addSeparator();
        widget->addAction(actUndo);
        widget->addAction(actRedo);
        widget->addAction(actDelete);
        widget->addSeparator();
        widget->addAction(actSelect);
        widget->addAction(actAddRelationship);

        retranslateUi(SqlDesigner);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SqlDesigner);
    } // setupUi

    void retranslateUi(QWidget *SqlDesigner)
    {
        actClearDiagram->setText(QApplication::translate("SqlDesigner", "Clear diagram", 0));
#ifndef QT_NO_TOOLTIP
        actClearDiagram->setToolTip(QApplication::translate("SqlDesigner", "Clear diagram", 0));
#endif // QT_NO_TOOLTIP
        actSelect->setText(QApplication::translate("SqlDesigner", "Select", 0));
#ifndef QT_NO_TOOLTIP
        actSelect->setToolTip(QApplication::translate("SqlDesigner", "Select", 0));
#endif // QT_NO_TOOLTIP
        actRedo->setText(QApplication::translate("SqlDesigner", "Redo", 0));
#ifndef QT_NO_TOOLTIP
        actRedo->setToolTip(QApplication::translate("SqlDesigner", "Redo", 0));
#endif // QT_NO_TOOLTIP
        actRedo->setShortcut(QApplication::translate("SqlDesigner", "Ctrl+Y", 0));
        actUndo->setText(QApplication::translate("SqlDesigner", "Undo", 0));
#ifndef QT_NO_TOOLTIP
        actUndo->setToolTip(QApplication::translate("SqlDesigner", "Undo", 0));
#endif // QT_NO_TOOLTIP
        actUndo->setShortcut(QApplication::translate("SqlDesigner", "Ctrl+Z", 0));
        actAddRelationship->setText(QApplication::translate("SqlDesigner", "Add relationship", 0));
#ifndef QT_NO_TOOLTIP
        actAddRelationship->setToolTip(QApplication::translate("SqlDesigner", "Add relationship", 0));
#endif // QT_NO_TOOLTIP
        actDelete->setText(QApplication::translate("SqlDesigner", "Delete", 0));
#ifndef QT_NO_TOOLTIP
        actDelete->setToolTip(QApplication::translate("SqlDesigner", "Delete", 0));
#endif // QT_NO_TOOLTIP
        actDelete->setShortcut(QApplication::translate("SqlDesigner", "Del", 0));
        rbCustom->setText(QApplication::translate("SqlDesigner", "Custom DS", 0));
        rbSql->setText(QApplication::translate("SqlDesigner", "SQL DS", 0));
        btnClose->setText(QApplication::translate("SqlDesigner", "Close", 0));
        groupBox->setTitle(QApplication::translate("SqlDesigner", "Connection's parameters", 0));
        label_2->setText(QApplication::translate("SqlDesigner", "Driver", 0));
        edtConnectionCoding->setText(QApplication::translate("SqlDesigner", "UTF8", 0));
        label_9->setText(QApplication::translate("SqlDesigner", "Charset coding", 0));
        label_6->setText(QApplication::translate("SqlDesigner", "Password", 0));
        cmbType->clear();
        cmbType->insertItems(0, QStringList()
         << QApplication::translate("SqlDesigner", "QSQLITE", 0)
         << QApplication::translate("SqlDesigner", "QMYSQL", 0)
         << QApplication::translate("SqlDesigner", "QMYSQL3", 0)
         << QApplication::translate("SqlDesigner", "QODBC", 0)
         << QApplication::translate("SqlDesigner", "QODBC3", 0)
         << QApplication::translate("SqlDesigner", "QPSQL", 0)
         << QApplication::translate("SqlDesigner", "QPSQL7", 0)
        );
        btnCheck->setText(QApplication::translate("SqlDesigner", "Check", 0));
        label_7->setText(QApplication::translate("SqlDesigner", "Connection", 0));
        label_5->setText(QApplication::translate("SqlDesigner", "User name", 0));
        label_8->setText(QApplication::translate("SqlDesigner", "Connection coding", 0));
        label_4->setText(QApplication::translate("SqlDesigner", "Host name", 0));
        edtCharsetCoding->setText(QApplication::translate("SqlDesigner", "UTF8", 0));
        label_3->setText(QApplication::translate("SqlDesigner", "DB name", 0));
        label_11->setText(QApplication::translate("SqlDesigner", "Connection name", 0));
        label_10->setText(QApplication::translate("SqlDesigner", "Port", 0));
        label->setText(QApplication::translate("SqlDesigner", "SQL query", 0));
        Q_UNUSED(SqlDesigner);
    } // retranslateUi

};

namespace Ui {
    class SqlDesigner: public Ui_SqlDesigner {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SQLDESIGNER_H
