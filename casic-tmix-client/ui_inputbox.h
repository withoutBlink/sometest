/********************************************************************************
** Form generated from reading UI file 'inputbox.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTBOX_H
#define UI_INPUTBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InputBox
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QWidget *TitleBar;
    QHBoxLayout *horizontalLayout;
    QLabel *Title;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *LBHint;
    QSpacerItem *verticalSpacer_3;
    QLineEdit *LEText;
    QLineEdit *LEText_2;
    QSpacerItem *verticalSpacer;
    QWidget *widget_3;
    QHBoxLayout *ToolBox;
    QPushButton *BtnAffirm;

    void setupUi(QDialog *InputBox)
    {
        if (InputBox->objectName().isEmpty())
            InputBox->setObjectName(QString::fromUtf8("InputBox"));
        InputBox->resize(736, 287);
        verticalLayout = new QVBoxLayout(InputBox);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(InputBox);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        TitleBar = new QWidget(widget);
        TitleBar->setObjectName(QString::fromUtf8("TitleBar"));
        TitleBar->setMinimumSize(QSize(0, 55));
        TitleBar->setMaximumSize(QSize(16777215, 55));
        horizontalLayout = new QHBoxLayout(TitleBar);
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(15, 0, 5, 0);
        Title = new QLabel(TitleBar);
        Title->setObjectName(QString::fromUtf8("Title"));

        horizontalLayout->addWidget(Title);


        verticalLayout_2->addWidget(TitleBar);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout_3 = new QVBoxLayout(widget_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(50, -1, 50, -1);
        LBHint = new QLabel(widget_2);
        LBHint->setObjectName(QString::fromUtf8("LBHint"));
        LBHint->setMinimumSize(QSize(0, 35));
        LBHint->setMaximumSize(QSize(16777215, 35));

        verticalLayout_3->addWidget(LBHint);

        verticalSpacer_3 = new QSpacerItem(20, 22, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        LEText = new QLineEdit(widget_2);
        LEText->setObjectName(QString::fromUtf8("LEText"));
        LEText->setMinimumSize(QSize(0, 40));
        LEText->setMaximumSize(QSize(16777215, 40));
        LEText->setProperty("XUIError", QVariant(false));

        verticalLayout_3->addWidget(LEText);

        LEText_2 = new QLineEdit(widget_2);
        LEText_2->setObjectName(QString::fromUtf8("LEText_2"));
        LEText_2->setMinimumSize(QSize(0, 40));
        LEText_2->setMaximumSize(QSize(16777215, 40));
        LEText_2->setProperty("XUIError", QVariant(false));

        verticalLayout_3->addWidget(LEText_2);

        verticalSpacer = new QSpacerItem(20, 22, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        verticalLayout_2->addWidget(widget_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setMinimumSize(QSize(0, 75));
        widget_3->setMaximumSize(QSize(16777215, 75));
        ToolBox = new QHBoxLayout(widget_3);
        ToolBox->setSpacing(10);
        ToolBox->setObjectName(QString::fromUtf8("ToolBox"));
        ToolBox->setContentsMargins(0, 0, 0, 0);
        BtnAffirm = new QPushButton(widget_3);
        BtnAffirm->setObjectName(QString::fromUtf8("BtnAffirm"));
        BtnAffirm->setMinimumSize(QSize(636, 40));
        BtnAffirm->setMaximumSize(QSize(636, 40));
        BtnAffirm->setFocusPolicy(Qt::NoFocus);

        ToolBox->addWidget(BtnAffirm);


        verticalLayout_2->addWidget(widget_3);


        verticalLayout->addWidget(widget);

        QWidget::setTabOrder(LEText, LEText_2);
        QWidget::setTabOrder(LEText_2, BtnAffirm);

        retranslateUi(InputBox);

        QMetaObject::connectSlotsByName(InputBox);
    } // setupUi

    void retranslateUi(QDialog *InputBox)
    {
        InputBox->setWindowTitle(QCoreApplication::translate("InputBox", "Dialog", nullptr));
        widget->setProperty("XUIStyleClass", QVariant(QCoreApplication::translate("InputBox", "Body", nullptr)));
        TitleBar->setProperty("XUIStyleClass", QVariant(QCoreApplication::translate("InputBox", "TitleBar", nullptr)));
        Title->setText(QCoreApplication::translate("InputBox", "\345\257\271\350\257\235\347\252\227\345\217\243\346\240\207\351\242\230", nullptr));
        LBHint->setText(QCoreApplication::translate("InputBox", "\345\257\271\350\257\235\347\252\227\345\217\243\346\217\220\347\244\272", nullptr));
        LEText->setPlaceholderText(QCoreApplication::translate("InputBox", "\347\254\254\344\270\200\346\254\241\346\211\213\345\212\250\350\276\223\345\205\245\346\210\226\346\211\253\347\240\201\346\236\252\346\211\253\346\217\217", nullptr));
        LEText_2->setPlaceholderText(QCoreApplication::translate("InputBox", "\347\254\254\344\272\214\346\254\241\346\211\213\345\212\250\350\276\223\345\205\245\346\210\226\346\211\253\347\240\201\346\236\252\346\211\253\346\217\217", nullptr));
        widget_3->setProperty("XUIStyleClass", QVariant(QCoreApplication::translate("InputBox", "TitleBar", nullptr)));
        BtnAffirm->setText(QCoreApplication::translate("InputBox", "\347\241\256 \350\256\244", nullptr));
        BtnAffirm->setProperty("XUIBtn", QVariant(QCoreApplication::translate("InputBox", "MsgBtnAffirm", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class InputBox: public Ui_InputBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTBOX_H
