#include "users.h"
#include "ui_users.h"

Users::Users(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Users)
{
    ui->setupUi(this);
    initModelUsers();
}

Users::~Users()
{
    delete ui;
}

void Users::initModelUsers()
{
    model = new QSqlRelationalTableModel(ui->tview);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);

    model->setTable("users");
    tidx = model->fieldIndex("role");
    model->setRelation(tidx, QSqlRelation("position_types", "id", "name"));
    ui->tview->setModel(model);

    ui->tview->hideColumn(model->fieldIndex("id"));
    ui->tview->hideColumn(model->fieldIndex("hash"));

    ui->tview->setColumnWidth(model->fieldIndex("user"), 120);
    ui->tview->setColumnWidth(model->fieldIndex("password"), 120);
    ui->tview->setColumnWidth(tidx, 140);

    model->setHeaderData(model->fieldIndex("user"), Qt::Horizontal, tr("Username"));
    model->setHeaderData(model->fieldIndex("password"), Qt::Horizontal, tr("Password"));
    model->setHeaderData(model->fieldIndex("role"), Qt::Horizontal, tr("Role"));

    ui->tview->verticalHeader()->setDefaultSectionSize(24);
    ui->tview->verticalHeader()->hide();
    ui->tview->horizontalHeader()->show();
//    ui->tview->setEditTriggers(QAbstractItemView::NoEditTriggers);

    model_t = new QSqlQueryModel();
    model_t->setQuery("SELECT id, name FROM position_types");
    ui->eType->setModel(model_t);
    ui->eType->setModelColumn(1);
    ui->eType->setCurrentIndex(-1);

    model->select();

}

void Users::on_bAdd_clicked()
{
    QSqlRecord rec_t = model_t->record(ui->eType->currentIndex());
    QString id_t = rec_t.value(rec_t.indexOf("id")).toString();
    QByteArray pwdhash = QCryptographicHash::hash(ui->ePassword->text().toUtf8(), QCryptographicHash::Sha1);
    QString pwdhashstr = QString(pwdhash);
    qDebug()<<"hashstr= "<<pwdhashstr;
    q.prepare("INSERT INTO users(user, password, hash, role) VALUES(:uname, :pass, :hash, :role)");
    q.bindValue(":uname", ui->eUsername->text());
    q.bindValue(":pass", ui->ePassword->text());
    q.bindValue(":hash", pwdhashstr);
    q.bindValue(":role", id_t);
    q.exec();
    model->select();
    ui->eUsername->clear();
    ui->ePassword->clear();
    ui->eType->setCurrentIndex(-1);
}

void Users::on_bDelete_clicked()
{
    QItemSelectionModel * sm = ui->tview->selectionModel();
    if (sm->hasSelection()){
        model->removeRow(sm->selectedRows().first().row());
        model->submitAll();
        model->select();
    }
}
