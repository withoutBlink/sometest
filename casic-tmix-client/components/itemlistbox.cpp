#include "itemlistbox.h"
#include "ui_itemlistbox.h"

#include "tstatus.h"
#include "wsroute.h"

#include "nlohmann/json.hpp"
#include "easylog/easylogging++.h"

#include <QHeaderView>

ItemListBox::ItemListBox(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ItemListBox)
{
	ui->setupUi(this);

	this->_RootNameList = {
		"版本测试",
		"手动测试",
		"功能测试",
		"压力测试",
		"确认测试"
	};

	QList<QTableWidget *> tables = {
		ui->TWItemList
	};

	foreach (QTableWidget *var, tables) {
		var->setColumnHidden(0, true);
		var->setShowGrid(false);
		var->setFocusPolicy(Qt::NoFocus);
		var->verticalHeader()->setVisible(false);
		var->verticalHeader()->setDefaultSectionSize(35);
		var->horizontalHeader()->setFixedHeight(35);
		var->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
		var->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
		var->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
		var->setSelectionBehavior(QAbstractItemView::SelectRows);
		var->setSelectionMode(QAbstractItemView::SingleSelection);
		var->setColumnWidth(2, 60);
	}

	connect(WsRoute::Instance(), SIGNAL(SignalItemResult(const QString&)),
		this, SLOT(UpdateItemResult(const QString&)));
}

ItemListBox::~ItemListBox()
{
	delete ui;
}

void ItemListBox::SetItemList(const QString &data)
{
	OnTestItemList(data);
}

void ItemListBox::UpdateItemResult(const QString &msg)
{
	try {
		nlohmann::json json = nlohmann::json::parse(msg.toUtf8());
		LOG(INFO) << json.dump(4);

		QTableWidget *table = ui->TWItemList;

		auto findlist = table->findItems(QString::number(json["Id"].get<uint>()), Qt::MatchExactly);
		foreach (auto var, findlist) {
			int row = table->row(var);
			if (table->item(row, 0)->text() == QString::number(json["Id"].get<uint>())
					&& table->item(row, 1)->text() == QString::fromUtf8(json["Name"].get<std::string>().c_str())
					&& table->item(row, 2)->text() == QString::fromUtf8(json["Standard"].get<std::string>().c_str())) {
				reinterpret_cast<TStatus *>(table->cellWidget(row, 3))->SetStatus(json["Result"].get<uint>());
				table->scrollToItem(table->item(row, 1));
				break;
			}
		}

	}  catch (std::exception &e) {
		LOG(ERROR) << e.what();
	}
}

void ItemListBox::OnTestItemList(const QString &msg)
{
	try {
		QTableWidget *table = ui->TWItemList;
		nlohmann::json json = nlohmann::json::parse(msg.toUtf8());
		LOG(INFO) << json.dump(4);
		if (json.is_array() && json.size()) {
			while (table->rowCount()) {
				table->removeRow(0);
			}
		}

		foreach (auto var, json) {
			int row = table->rowCount();
			table->insertRow(row);
			table->setItem(row, 0, new QTableWidgetItem(QString::number(var["Id"].get<int>())));
			table->setItem(row, 1, new QTableWidgetItem(QString::fromUtf8(var["Name"].get<std::string>().c_str())));
			table->setItem(row, 2, new QTableWidgetItem(QString::fromUtf8(var["Standard"].get<std::string>().c_str())));
			table->setCellWidget(row, 3, new TStatus(table, var["Result"].get<uint>()));
		}

	}  catch (std::exception &e) {
		LOG(ERROR) << e.what();
	}
}
