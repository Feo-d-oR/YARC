#ifndef EDITDIAGREPORT_H
#define EDITDIAGREPORT_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class EditDiagReport;
}

class EditDiagReport : public QDialog
{
    Q_OBJECT

public:
    explicit EditDiagReport(QWidget *parent = 0);
    ~EditDiagReport();

private:
    Ui::EditDiagReport *ui;
};

#endif // EDITDIAGREPORT_H
