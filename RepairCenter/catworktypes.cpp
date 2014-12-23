#include "catworktypes.h"
#include "ui_catworktypes.h"

CatWorkTypes::CatWorkTypes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CatWorkTypes)
{
    ui->setupUi(this);
    initModel();
}

CatWorkTypes::~CatWorkTypes()
{
    delete ui;
}

void CatWorkTypes::initModel()
{
    model = new QSqlTableModel(ui->tview);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("works");
    ui->tview->setModel(model);

    ui->tview->setColumnWidth(model->fieldIndex("id"), 50);
    model->setHeaderData(model->fieldIndex("id"), Qt::Horizontal, "ID");
    ui->tview->setColumnWidth(model->fieldIndex("name"), 250);
    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, "Наименование");
    ui->tview->setColumnWidth(model->fieldIndex("price"), 70);
    model->setHeaderData(model->fieldIndex("price"), Qt::Horizontal, "Стоимость");
    ui->tview->setColumnWidth(model->fieldIndex("comment"), 250);
    model->setHeaderData(model->fieldIndex("comment"), Qt::Horizontal, "Примечание");
    ui->tview->verticalHeader()->setDefaultSectionSize(24);
    ui->tview->verticalHeader()->hide();
    ui->tview->horizontalHeader()->show();

    model->select();
}

void CatWorkTypes::on_bAdd_clicked()
{
    model->insertRows(model->rowCount(), 1);
    ui->tview->setCurrentIndex(model->index(model->rowCount()-1, 1));
}

void CatWorkTypes::on_bSave_clicked()
{
    model->submitAll();
}

void CatWorkTypes::on_bClose_clicked()
{
    model->revertAll();
    close();
}

void CatWorkTypes::on_bDelete_clicked()
{
    QItemSelectionModel *sm = ui->tview->selectionModel();
    if (sm->hasSelection()){
        model->removeRow(sm->selectedRows().first().row());
        model->submitAll();
        model->select();
    }
}

void CatWorkTypes::on_eSearchText_textEdited(const QString &arg1)
{
    if(arg1 != "")
    {
        model->setFilter("name LIKE '%" + arg1 + "%'");
        qDebug() << "filter:" << model->filter();
    }
    else model->setFilter(QString());
}
