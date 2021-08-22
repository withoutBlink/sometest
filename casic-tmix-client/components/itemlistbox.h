#ifndef ITEMLISTBOX_H
#define ITEMLISTBOX_H

#include <QWidget>

namespace Ui {
class ItemListBox;
}

class ItemListBox : public QWidget
{
	Q_OBJECT

public:
	explicit ItemListBox(QWidget *parent = nullptr);
	~ItemListBox();

	void SetItemList(const QString& data);

private:
	void OnTestItemList(const QString& msg);

private slots:
	void UpdateItemResult(const QString& msg);

private:
	Ui::ItemListBox *ui;
	QList<QString> _RootNameList;
};

#endif // ITEMLISTBOX_H
