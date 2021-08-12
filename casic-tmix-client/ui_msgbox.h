/********************************************************************************
** Form generated from reading UI file 'msgbox.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSGBOX_H
#define UI_MSGBOX_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MsgBox
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QWidget *TitleBar;
    QHBoxLayout *horizontalLayout;
    QLabel *Title;
    QPushButton *BtnMinimized;
    QPushButton *BtnClose;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *LBIcon;
    QLabel *LBText;
    QWidget *widget_3;
    QHBoxLayout *ToolBox;

    void setupUi(QDialog *MsgBox)
    {
        if (MsgBox->objectName().isEmpty())
            MsgBox->setObjectName(QString::fromUtf8("MsgBox"));
        MsgBox->resize(736, 286);
        verticalLayout = new QVBoxLayout(MsgBox);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(MsgBox);
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

        BtnMinimized = new QPushButton(TitleBar);
        BtnMinimized->setObjectName(QString::fromUtf8("BtnMinimized"));
        BtnMinimized->setMinimumSize(QSize(55, 55));
        BtnMinimized->setMaximumSize(QSize(55, 55));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/static/images/icon_min.svg"), QSize(), QIcon::Normal, QIcon::Off);
        BtnMinimized->setIcon(icon);

        horizontalLayout->addWidget(BtnMinimized);

        BtnClose = new QPushButton(TitleBar);
        BtnClose->setObjectName(QString::fromUtf8("BtnClose"));
        BtnClose->setMinimumSize(QSize(55, 55));
        BtnClose->setMaximumSize(QSize(55, 55));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/static/images/icon_close.svg"), QSize(), QIcon::Normal, QIcon::Off);
        BtnClose->setIcon(icon1);

        horizontalLayout->addWidget(BtnClose);


        verticalLayout_2->addWidget(TitleBar);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(25);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(30, 0, 0, 0);
        LBIcon = new QLabel(widget_2);
        LBIcon->setObjectName(QString::fromUtf8("LBIcon"));
        LBIcon->setMinimumSize(QSize(128, 128));
        LBIcon->setMaximumSize(QSize(128, 128));

        horizontalLayout_2->addWidget(LBIcon);

        LBText = new QLabel(widget_2);
        LBText->setObjectName(QString::fromUtf8("LBText"));

        horizontalLayout_2->addWidget(LBText);


        verticalLayout_2->addWidget(widget_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setMinimumSize(QSize(0, 75));
        widget_3->setMaximumSize(QSize(16777215, 75));
        ToolBox = new QHBoxLayout(widget_3);
        ToolBox->setSpacing(10);
        ToolBox->setObjectName(QString::fromUtf8("ToolBox"));
        ToolBox->setContentsMargins(0, 0, 0, 0);

        verticalLayout_2->addWidget(widget_3);


        verticalLayout->addWidget(widget);


        retranslateUi(MsgBox);

        QMetaObject::connectSlotsByName(MsgBox);
    } // setupUi

    void retranslateUi(QDialog *MsgBox)
    {
        MsgBox->setWindowTitle(QCoreApplication::translate("MsgBox", "Dialog", nullptr));
        widget->setProperty("XUIStyleClass", QVariant(QCoreApplication::translate("MsgBox", "Body", nullptr)));
        TitleBar->setProperty("XUIStyleClass", QVariant(QCoreApplication::translate("MsgBox", "TitleBar", nullptr)));
        Title->setText(QCoreApplication::translate("MsgBox", "\346\240\207\351\242\230", nullptr));
        BtnMinimized->setText(QString());
        BtnClose->setText(QString());
        BtnClose->setProperty("XUIBtn", QVariant(QCoreApplication::translate("MsgBox", "BtnClose", nullptr)));
        LBIcon->setText(QString());
        LBText->setText(QCoreApplication::translate("MsgBox", "\346\217\220\347\244\272\346\226\207\345\255\227", nullptr));
        widget_3->setProperty("XUIStyleClass", QVariant(QCoreApplication::translate("MsgBox", "TitleBar", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class MsgBox: public Ui_MsgBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSGBOX_H
