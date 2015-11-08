#include "partswidgetstorekeeper.h"
#include "ui_partswidgetstorekeeper.h"

PartsWidgetStorekeeper::PartsWidgetStorekeeper(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PartsWidgetStorekeeper)
{
    ui->setupUi(this);
}

PartsWidgetStorekeeper::~PartsWidgetStorekeeper()
{
    delete ui;
}
