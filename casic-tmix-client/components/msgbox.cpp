#include "msgbox.h"
#include "ui_msgbox.h"

#include "easylog/easylogging++.h"

#include <QStyle>
#include <QMouseEvent>

int MsgBox::MsgFromJson(const nlohmann::json &json, QWidget *parent)
{
	int ret = -1;
	try {
		LOG(DEBUG) << json.dump(4);
		MsgBox *msgbox = new MsgBox(parent);
		msgbox->SetIcon(static_cast<MsgBox::Icon>(json["Icon"].get<int>()));
		msgbox->SetTitle(QString::fromUtf8(json["Title"].get<std::string>().c_str()));
		msgbox->SetText(QString::fromUtf8(json["Text"].get<std::string>().c_str()));
		do {
			if (!json.contains("Btns") || !json["Btns"].is_array() || json["Btns"].size() == 0) {
				break;
			}

			foreach (auto& var, json["Btns"]) {
				QPushButton *btn = new QPushButton(QString::fromUtf8(var["Text"].get<std::string>().c_str()));
				if (var.contains("Property") && var["Property"].is_string()) {
					QString property = QString::fromUtf8(var["Property"].get<std::string>().c_str());
					btn->setProperty("XUIBtn", "MsgBtn" + property);
				} else {
					btn->setProperty("XUIBtn", "MsgBtnDefault");
				}

				msgbox->AddButton(btn);
				btn->setFixedSize(135, 35);
				btn->setProperty("Id", var["Id"].get<int>());
				btn->style()->unpolish(btn);
				btn->style()->polish(btn);
				btn->update();
				connect(btn, &QPushButton::clicked, [=]() {
					msgbox->done(btn->property("Id").toInt());
				});
			}
		} while(false);

		ret = msgbox->exec();

	} catch (std::exception &e) {
		LOG(ERROR) << e.what();
	}

	return ret;
}

//int MsgBox::InformationBox(MsgBox::Icon icon, const QString &title, const QString &text, QWidget *parent)
//{
//	MsgBox *box = new MsgBox();
//}

//int MsgBox::WarningBox(MsgBox::Icon icon, const QString &title, const QString &text, QWidget *parent)
//{

//}

//int MsgBox::CriticalBox(MsgBox::Icon icon, const QString &title, const QString &text, QWidget *parent)
//{

//}

//int MsgBox::QuestionBox(MsgBox::Icon icon, const QString &title, const QString &text, QWidget *parent)
//{

//}

MsgBox::MsgBox(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::MsgBox)
{
	ui->setupUi(this);

	this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

	this->_Movie.setScaledSize(QSize(128, 128));
}

MsgBox::~MsgBox()
{
	delete ui;
}

void MsgBox::SetIcon(MsgBox::Icon icon)
{
	this->_Movie.stop();
	ui->LBIcon->show();
	switch (icon) {
	case MsgBox::NoIcon:
		ui->LBIcon->hide();
		break;
	case MsgBox::Information:
		this->_Movie.setFileName(":/static/images/icon_information.gif");
		break;
	case MsgBox::Warning:
		this->_Movie.setFileName(":/static/images/icon_warning.gif");
		break;
	case MsgBox::Critical:
		this->_Movie.setFileName(":/static/images/icon_failed.gif");
		break;
	case MsgBox::Question:
		this->_Movie.setFileName(":/static/images/icon_question.gif");
		break;
	default:
		break;
	}
	ui->LBIcon->setMovie(&this->_Movie);
	this->_Movie.start();
}

void MsgBox::SetTitle(const QString &title)
{
	ui->Title->setText(title);
}

void MsgBox::SetText(const QString &text)
{
	ui->LBText->setText(text);
}

void MsgBox::AddButton(QPushButton *btns)
{
	ui->ToolBox->addWidget(btns);
}

void MsgBox::SetButton(QList<QPushButton *> btns)
{
	QList<QPushButton *> btnlist = ui->ToolBox->findChildren<QPushButton *>();
	foreach (auto var, btnlist) {
		ui->ToolBox->removeWidget(var);
		var->deleteLater();
		var = nullptr;
	}

	foreach (auto var, btns) {
		ui->ToolBox->addWidget(var);
	}
}

void MsgBox::on_BtnClose_clicked()
{
	this->done(-1);
}

void MsgBox::on_BtnMinimized_clicked()
{
	this->showMinimized();
}

void MsgBox::mouseMoveEvent(QMouseEvent *event)
{
	if (this->_MousePressed && (event->buttons() & Qt::LeftButton)) {
		this->move(event->globalPos() - this->_MousePoint);
		event->accept();
	}
}

void MsgBox::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		this->_MousePressed = true;
		this->_MousePoint = event->globalPos() - this->pos();
		event->accept();
	}
}

void MsgBox::mouseReleaseEvent(QMouseEvent *)
{
	this->_MousePressed = false;
}

