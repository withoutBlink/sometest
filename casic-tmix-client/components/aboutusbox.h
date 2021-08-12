#ifndef ABOUTUSBOX_H
#define ABOUTUSBOX_H

#include <QDialog>

namespace Ui {
class AboutUSBox;
}

class AboutUSBox : public QDialog
{
    Q_OBJECT

public:
    explicit AboutUSBox(QWidget *parent = nullptr);
    ~AboutUSBox();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::AboutUSBox *ui;
    bool _MousePressed;
    QPoint _MousePoint;
};

#endif // ABOUTUSBOX_H
