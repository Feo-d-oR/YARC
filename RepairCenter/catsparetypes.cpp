#include "catsparetypes.h"
#include "ui_catsparetypes.h"

CatSpareTypes::CatSpareTypes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CatSpareTypes)
{
    ui->setupUi(this);
    initModel();
}

CatSpareTypes::~CatSpareTypes()
{
    delete ui;
}


void CatSpareTypes::initModel()
{
    model = new QSqlTableModel(ui->tview);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("spare_types");
    ui->tview->setModel(model);

    ui->tview->hideColumn(model->fieldIndex("id"));
    ui->tview->setColumnWidth(model->fieldIndex("name"), 250);
    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    ui->tview->verticalHeader()->setDefaultSectionSize(24);
    ui->tview->verticalHeader()->hide();
    ui->tview->horizontalHeader()->show();

    model->select();
}

void CatSpareTypes::on_bAdd_clicked()
{
    model->insertRows(model->rowCount(), 1);
    ui->tview->setCurrentIndex(model->index(model->rowCount()-1, 1));
}

void CatSpareTypes::on_bSave_clicked()
{
    model->submitAll();
}

void CatSpareTypes::on_bClose_clicked()
{
    model->revertAll();
    close();
}

void CatSpareTypes::on_bDelete_clicked()
{
    model->revertAll();
    QItemSelectionModel *sm = ui->tview->selectionModel();
    if (sm->hasSelection()){
        model->removeRow(sm->selectedRows().first().row());
        model->submitAll();
        model->select();
    }
}
