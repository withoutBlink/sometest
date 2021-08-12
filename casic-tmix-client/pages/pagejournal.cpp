#include "pagejournal.h"
#include "ui_pagejournal.h"

PageJournal::PageJournal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageJournal)
{
    ui->setupUi(this);
}

PageJournal::~PageJournal()
{
    delete ui;
}
