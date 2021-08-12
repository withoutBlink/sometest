/********************************************************************************
** Form generated from reading UI file 'ctlbtnbox.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CTLBTNBOX_H
#define UI_CTLBTNBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CtlBtnBox
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_6;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;

    void setupUi(QWidget *CtlBtnBox)
    {
        if (CtlBtnBox->objectName().isEmpty())
            CtlBtnBox->setObjectName(QString::fromUtf8("CtlBtnBox"));
        CtlBtnBox->resize(729, 165);
        gridLayout = new QGridLayout(CtlBtnBox);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(CtlBtnBox);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(0, 35));
        widget_2->setMaximumSize(QSize(16777215, 35));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(15, 0, 0, 0);
        label = new QLabel(widget_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton = new QPushButton(widget_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget_3);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton_6 = new QPushButton(widget_3);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        horizontalLayout_2->addWidget(pushButton_6);

        pushButton_3 = new QPushButton(widget_3);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_2->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(widget_3);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        horizontalLayout_2->addWidget(pushButton_4);


        verticalLayout->addWidget(widget_3);


        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(CtlBtnBox);

        QMetaObject::connectSlotsByName(CtlBtnBox);
    } // setupUi

    void retranslateUi(QWidget *CtlBtnBox)
    {
        CtlBtnBox->setWindowTitle(QCoreApplication::translate("CtlBtnBox", "Form", nullptr));
        widget->setProperty("XUIStyleClass", QVariant(QCoreApplication::translate("CtlBtnBox", "Content", nullptr)));
        widget_2->setProperty("XUIStyleClass", QVariant(QCoreApplication::translate("CtlBtnBox", "TitleBar", nullptr)));
        widget_2->setProperty("XUIRound", QVariant(QCoreApplication::translate("CtlBtnBox", "SmallRound", nullptr)));
        label->setText(QCoreApplication::translate("CtlBtnBox", "\346\216\247\345\210\266\344\270\255\345\277\203", nullptr));
        label->setProperty("XUIFont", QVariant(QCoreApplication::translate("CtlBtnBox", "Medium", nullptr)));
        pushButton->setText(QCoreApplication::translate("CtlBtnBox", "PushButton", nullptr));
        pushButton_2->setText(QCoreApplication::translate("CtlBtnBox", "PushButton", nullptr));
        pushButton_6->setText(QCoreApplication::translate("CtlBtnBox", "PushButton", nullptr));
        pushButton_3->setText(QCoreApplication::translate("CtlBtnBox", "PushButton", nullptr));
        pushButton_4->setText(QCoreApplication::translate("CtlBtnBox", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CtlBtnBox: public Ui_CtlBtnBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CTLBTNBOX_H
