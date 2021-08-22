#include "pagetoolboxes.h"
#include "ui_pagetoolboxes.h"

PageToolboxes::PageToolboxes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageToolboxes)
{
    ui->setupUi(this);
}

PageToolboxes::~PageToolboxes()
{
    delete ui;
}
