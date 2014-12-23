/*
Name: QtRptDesigner
Version: 1.4.5
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net
2012-2014
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QDomDocument>
#include "aboutDlg.h"
#include "RepScrollArea.h"
#include "SettingDlg.h"
#include <downloadmanager.h>
#include "SqlDesigner.h"
#include "TContainerLine.h"
#include "UndoCommands.h"

namespace Ui {
    class MainWindow;
}

class EditorDelegate: public QItemDelegate
{
    Q_OBJECT
public:
    EditorDelegate(QObject *parent);
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const {
        Q_UNUSED(option);
        Q_UNUSED(index);
        return QSize(50,20);
    }
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

protected:
    void paint( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;

private slots:
    void commitAndCloseEditor();
    void editorClose_(QWidget *editor, QAbstractItemDelegate::EndEditHint hint);

signals:
    void editorClose(QItemDelegate *item);
    void btnClicked();
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setContainerConnections(RptContainer *cont);
    QUndoStack *m_undoStack;
    QWidget *widgetInFocus;

protected:
    bool eventFilter(QObject *obj, QEvent *e);
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    QListWidget *listFrameStyle;
    QDomDocument *xmlDoc;    
    QTreeWidgetItem *rootItem;    
    RptContainer *m_newContainer;
    RptContainer *cloneCont;
    QList<RptContainer *> *cloneContList;
    QList<RptContainer *> *newContList;
    QFontComboBox *cbFontName;
    QComboBox *cbZoom;
    QComboBox *cbFontSize;
    QComboBox *cbFrameWidth;
    bool newContMoving;
    QIcon icon;
    QString fileName;
    QMenu *contMenu;
    QMenu *bandMenu;

    QAction *actRepTitle;
    QAction *actReportSummary;
    QAction *actPageHeader;
    QAction *actPageFooter;
    QAction *actMasterData;
    QAction *actMasterFooter;
    QAction *actMasterHeader;
    QAction *separatorAct;
    QAction *actDataGroupingHeader;
    QAction *actDataGroupingFooter;

    SqlDesigner *sqlDesigner;

    enum { MaxRecentFiles = 5 };
    QAction *recentFileActs[MaxRecentFiles];

    bool setXMLProperty(QDomElement *repElem, QWidget *widget);
    void selectItemInTree(QTreeWidgetItem *item);
    void showParamState();
    Command getCommand(QObject *obj);
    void execButtonCommand(Command command, QVariant value);
    void processCommand(Command command, QVariant value, QWidget *widget);
    QTreeWidgetItem *findItemInTree(Command command);
    void generateName(RptContainer *cont);
    void setParamTree(Command command, QVariant value = 0, bool child = false);
    void updateRecentFileActions();
    void setCurrentFile(const QString &fileName);
    QDomElement getDataSourceElement(QDomNode n);
    void addContainer(RptContainer *container);
    void shiftToDelta(QRect oldRect, QRect newRect, QObject *sender, bool change);
    void enableAdding();
    QList<RptContainer *> getSelectedContainer();

private slots:
    void showAbout();
    void openFile();
    void newReport();
    void saveReport();
    void showPageSetting();
    void clickOnTBtn();
    void addBand();
    void addFieldText();
    void addFieldTextRich();
    void addField(FieldType type);
    void AddPicture();
    void addDiagram();
    void addDraw();
    void addBarcode();
    void setWidgetInFocus(bool inFocus);
    void delItemInTree(QTreeWidgetItem *);
    void selTree(QTreeWidgetItem *item, int);
    void itemChanged(QTreeWidgetItem *item, int column);
    void closeEditor();
    void changeTextFont();
    void contGeomChanging(QRect oldRect, QRect newRect);
    void contGeomChanged(QRect oldRect, QRect newRect);
    void clipBoard();
    void chooseColor();
    void showFrameStyle(QPoint pos);
    void setFrameStyle(QListWidgetItem * item);
    void changeFrameWidth();
    void bandResing(int value);
    void reportPageChanged(int index);
    void newReportPage();
    void deleteReportPage();
    void alignFields();
    void openRecentFile();
    void closeProgram();
    void showSetting();
    void changeZoom();
    void openDBGroupProperty();
    void checkUpdates();
    void showPreview();
    void showDataSource();
    void undo();
    void redo();
    void openReadme();
    void deleteByUser();
};

MainWindow *getMW();

#endif // MAINWINDOW_H
