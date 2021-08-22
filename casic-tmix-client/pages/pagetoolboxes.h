#ifndef PAGETOOLBOXES_H
#define PAGETOOLBOXES_H

#include <QWidget>

namespace Ui {
class PageToolboxes;
}

class PageToolboxes : public QWidget
{
    Q_OBJECT

public:
    explicit PageToolboxes(QWidget *parent = nullptr);
    ~PageToolboxes();

private:
    Ui::PageToolboxes *ui;
};

#endif // PAGETOOLBOXES_H
