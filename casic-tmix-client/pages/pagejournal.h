#ifndef PAGEJOURNAL_H
#define PAGEJOURNAL_H

#include <QWidget>

namespace Ui {
class PageJournal;
}

class PageJournal : public QWidget
{
    Q_OBJECT

public:
    explicit PageJournal(QWidget *parent = nullptr);
    ~PageJournal();

private:
    Ui::PageJournal *ui;
};

#endif // PAGEJOURNAL_H
