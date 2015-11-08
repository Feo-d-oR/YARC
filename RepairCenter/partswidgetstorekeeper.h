#ifndef PARTSWIDGETSTOREKEEPER_H
#define PARTSWIDGETSTOREKEEPER_H

#include <QWidget>

namespace Ui {
class PartsWidgetStorekeeper;
}

class PartsWidgetStorekeeper : public QWidget
{
    Q_OBJECT

public:
    explicit PartsWidgetStorekeeper(QWidget *parent = 0);
    ~PartsWidgetStorekeeper();

private:
    Ui::PartsWidgetStorekeeper *ui;
};

#endif // PARTSWIDGETSTOREKEEPER_H
