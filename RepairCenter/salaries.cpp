#include "salaries.h"
#include "ui_salaries.h"

Salaries::Salaries(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Salaries)
{
    ui->setupUi(this);
    setModels();
    calcSummFirm();
}

Salaries::~Salaries()
{
    delete ui;
}

void Salaries::setModels()
{
    model_e = new QSqlQueryModel();
    model_e->setQuery("SELECT id, name FROM employees WHERE isactive = '1'");
    ui->eEmployee->setModel(model_e);
    ui->eEmployee->setModelColumn(1);
    ui->eEmployee->model()->sort(1, Qt::AscendingOrder);
    ui->eEmployee->setCurrentIndex(-1);
}

void Salaries::calcSummEmpl()
{
    q.exec("SELECT SUM(summ) FROM salaries WHERE employee = "+ emplID);
    q.first();
    qDebug() << "emplID: " << q.value(0).toFloat();
    qDebug() << "emplsal: " << q.value(0).toFloat();
    summ = q.value(0).toFloat();
    ui->eSummEmp->setText(st.setNum(summ));
}

void Salaries::calcSummFirm()
{
    q.exec("SELECT SUM(summ) FROM salaries WHERE employee = -5");
    q.first();
    qDebug() << "firmsal: " << q.value(0).toFloat();
    summ = q.value(0).toFloat();
    ui->eSummFirm->setText(st.setNum(summ));
}

void Salaries::on_eEmployee_currentIndexChanged(int index)
{
    if (index != -1)
    {
        rec_e = model_e->record(ui->eEmployee->currentIndex());
        emplID = rec_e.value(rec_e.indexOf("id")).toString();
        calcSummEmpl();
    }
}

void Salaries::on_bPayEmp_clicked()
{
    summ = ui->eSummEmp->text().toFloat();
    q.exec(QString("INSERT INTO salaries VALUES (NULL, "+ emplID +", "+ st.setNum(-summ) +")"));
    calcSummEmpl();
    calcSummFirm();
}

void Salaries::on_bGetProfit_clicked()
{
    summ = ui->eSummFirm->text().toFloat();
    q.exec(QString("INSERT INTO salaries VALUES (NULL, -5, "+ st.setNum(-summ) +")"));
    calcSummFirm();
}
