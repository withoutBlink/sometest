#ifndef PAGEHOME_H
#define PAGEHOME_H

#include <QWidget>

namespace Ui {
class PageHome;
}

class PageHome : public QWidget
{
    Q_OBJECT

public:
    explicit PageHome(QWidget *parent = nullptr);
    ~PageHome();

signals:
    void onStarted();

private slots:
    void on_BtnStarted_clicked();

private:
    Ui::PageHome *ui;
};

#endif // PAGEHOME_H
