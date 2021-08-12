#include "inputbox.h"
#include "ui_inputbox.h"

#include "easylog/easylogging++.h"

#include <QStyle>
#include <QMouseEvent>

QString InputBox::MsgFromJson(const nlohmann::json &json, QWidget *parent)
{
	QString ret;
	try {
		LOG(DEBUG) << json.dump(4);
		InputBox *inputbox = new InputBox(parent);

//		if (json.contains("NotEmpty") && json["NotEmpty"].is_boolean()) {
//			inputbox->SetNotEmpty(json["NotEmpty"].get<bool>());
//		}

		if (json.contains("Title") && json["Title"].is_string()) {
			inputbox->SetTitle(QString::fromUtf8(json["Title"].get<std::string>().c_str()));
		}

		if (json.contains("Text") && json["Text"].is_string()) {
			inputbox->SetText(QString::fromUtf8(json["Text"].get<std::string>().c_str()));
		}

//		if (json.contains("PlaceholderText") && json["PlaceholderText"].is_string()) {
//			inputbox->SetPlaceholderTest(QString::fromUtf8(json["PlaceholderText"].get<std::string>().c_str()));
//		}

		if (json.contains("ReadOnly") && json["ReadOnly"].is_boolean()) {
			inputbox->SetReadOnly(json["ReadOnly"].get<bool>());
		} else {
			inputbox->SetReadOnly(false);
		}

		if (json.contains("Validator") && json["Validator"].is_string()) {
			inputbox->SetValidator(QString::fromUtf8(json["Validator"].get<std::string>().c_str()));
		}

		if (inputbox->exec() == 0) {
			ret = inputbox->GetResult();
		}

	} catch (std::exception &e) {
		LOG(ERROR) << e.what();
	}

	return ret;
}

InputBox::InputBox(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::InputBox)
	, _NotEmpty(false)
	, _CheckOutRegExpValidator(nullptr)
{
	ui->setupUi(this);

	this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

	QList<QLineEdit *> list = ui->widget_2->findChildren<QLineEdit *>();
	foreach (auto lineedit, list) {
		lineedit->installEventFilter(this);
	}
//	this->clearFocus();
//	ui->LEText->setFocus();
}

InputBox::~InputBox()
{
	delete ui;
}

void InputBox::SetTitle(const QString &title)
{
	ui->Title->setText(title);
}

void InputBox::SetText(const QString &text)
{
	if (this->_NotEmpty) {
		ui->LBHint->setText(text + "（输入不允许为空！）");
	} else {
		ui->LBHint->setText(text);
	}
}

void InputBox::SetReadOnly(bool readonly)
{
	ui->LEText->setReadOnly(readonly);
}

//void InputBox::SetNotEmpty(bool notempty)
//{
//	this->_NotEmpty = notempty;
//	if (notempty) {
//		ui->BtnClose->setDisabled(true);
//		ui->BtnMinimized->setDisabled(true);
//		ui->BtnCancel->setDisabled(true);
//	} else {
//		ui->BtnClose->setDisabled(false);
//		ui->BtnMinimized->setDisabled(false);
//		ui->BtnCancel->setDisabled(false);
//	}
//}

void InputBox::SetPlaceholderTest(const QString &ptext)
{
	ui->LEText->setPlaceholderText(ptext);
}

void InputBox::AddButton(QPushButton *btns)
{
	ui->ToolBox->addWidget(btns);
}

void InputBox::SetButton(QList<QPushButton *> btns)
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

void InputBox::SetValidator(const QString &validator)
{
	if (validator.isEmpty()) {
		return ;
	}
	this->_CheckOutRegExp.setPatternSyntax(QRegExp::RegExp);
	this->_CheckOutRegExp.setCaseSensitivity(Qt::CaseSensitive);
	this->_CheckOutRegExp.setPattern(validator);

	if (this->_CheckOutRegExpValidator) {
		this->_CheckOutRegExpValidator->deleteLater();
		this->_CheckOutRegExpValidator = nullptr;
	}

	this->_CheckOutRegExpValidator = new QRegExpValidator(this->_CheckOutRegExp, this);
	ui->LEText->setValidator(this->_CheckOutRegExpValidator);
	ui->LEText_2->setValidator(this->_CheckOutRegExpValidator);
}

QString InputBox::GetResult()
{
	return ui->LEText->text();
}

//void InputBox::on_BtnClose_clicked()
//{
//	this->done(-1);
//}

//void InputBox::on_BtnMinimized_clicked()
//{
//	this->showMinimized();
//}

void InputBox::mouseMoveEvent(QMouseEvent *event)
{
	if (this->_MousePressed && (event->buttons() & Qt::LeftButton)) {
		this->move(event->globalPos() - this->_MousePoint);
		event->accept();
	}
}

void InputBox::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		this->_MousePressed = true;
		this->_MousePoint = event->globalPos() - this->pos();
		event->accept();
	}
}

void InputBox::mouseReleaseEvent(QMouseEvent *)
{
	this->_MousePressed = false;
}

bool InputBox::eventFilter(QObject *watched, QEvent *event)
{
	bool ret = false;
	do {
		QList<QLineEdit *> list = ui->widget_2->findChildren<QLineEdit *>();
		QLineEdit *lineedit = reinterpret_cast<QLineEdit *>(watched);
		if (list.indexOf(lineedit) == -1) {   /* 不是LineEdit跳过 */
			break;
		}

		switch (event->type()) {
		case QEvent::FocusIn:
			this->setError(lineedit, false);
			break;

		case QEvent::KeyPress:  /* 键盘事件 */
			if(reinterpret_cast<QKeyEvent *>(event)->key() == Qt::Key_Enter ||
					reinterpret_cast<QKeyEvent *>(event)->key() == Qt::Key_Return) {
				emit lineedit->editingFinished();
			} else if (reinterpret_cast<QKeyEvent *>(event)->key() == Qt::Key_Escape) {
				ret = true;
			}
			break;

		default:                /* 其他事件 */
			break;
		}
	} while (false);

	return ret ? true : QWidget::eventFilter(watched, event);
}

void InputBox::on_BtnAffirm_clicked()
{
	QString input = ui->LEText->text();
	QString input2 = ui->LEText_2->text();
	if (input.isEmpty()) {
		this->setError(ui->LEText);
	} else if (input2.isEmpty()) {
		this->setError(ui->LEText_2);
	} else if (input != input2) {
		this->setError(ui->LEText);
		this->setError(ui->LEText_2);
	} else {
		this->done(0);
	}
}

void InputBox::on_LEText_editingFinished()
{
	if (ui->LEText->text().isEmpty()) {
		this->setError(ui->LEText);
	} else {
		this->focusNextChild();
	}
}

void InputBox::on_LEText_2_editingFinished()
{
	if (ui->LEText_2->text().isEmpty()) {
		this->setError(ui->LEText_2);
	} else {
		this->on_BtnAffirm_clicked();
	}
}

template<typename T>
void InputBox::setError(T obj, bool err)
{
	obj->setProperty("XUIError", err);
	obj->style()->unpolish(obj);
	obj->style()->polish(obj);
	obj->update();
	this->setStyle(QApplication::style());
}
