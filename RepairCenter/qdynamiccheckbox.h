#ifndef QDYNAMICCHECKBOX_H
#define QDYNAMICCHECKBOX_H

#include <QCheckBox>

class qDynamicCheckBox : public QCheckBox
{
    Q_OBJECT
public:
    explicit qDynamicCheckBox(QWidget *parent = 0);
    ~qDynamicCheckBox();
    static int checkID;
    QString getID();
    void setID(QString id);

public slots:

private:
    QString chboxID = 0;

};

#endif // QDYNAMICCHECKBOX_H
