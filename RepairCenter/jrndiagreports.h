#ifndef JRNDIAGREPORTS_H
#define JRNDIAGREPORTS_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class JrnDiagReports;
}

class JrnDiagReports : public QDialog
{
    Q_OBJECT

public:
    explicit JrnDiagReports(QWidget *parent = 0);
    ~JrnDiagReports();

private:
    Ui::JrnDiagReports *ui;
};

#endif // JRNDIAGREPORTS_H
