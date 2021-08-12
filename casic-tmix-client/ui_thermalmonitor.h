/********************************************************************************
** Form generated from reading UI file 'thermalmonitor.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THERMALMONITOR_H
#define UI_THERMALMONITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "dashboard.h"

QT_BEGIN_NAMESPACE

class Ui_ThermalMonitor
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *TitleBar;
    QHBoxLayout *horizontalLayout;
    QLabel *Title;
    QWidget *widget_4;
    QGridLayout *gridLayout_2;
    DashBoard *WGDashBoard;

    void setupUi(QWidget *ThermalMonitor)
    {
        if (ThermalMonitor->objectName().isEmpty())
            ThermalMonitor->setObjectName(QString::fromUtf8("ThermalMonitor"));
        ThermalMonitor->resize(260, 245);
        ThermalMonitor->setMinimumSize(QSize(260, 0));
        ThermalMonitor->setMaximumSize(QSize(260, 16777215));
        gridLayout = new QGridLayout(ThermalMonitor);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(ThermalMonitor);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        TitleBar = new QWidget(widget);
        TitleBar->setObjectName(QString::fromUtf8("TitleBar"));
        TitleBar->setMinimumSize(QSize(0, 35));
        TitleBar->setMaximumSize(QSize(16777215, 35));
        TitleBar->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout = new QHBoxLayout(TitleBar);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(15, 0, 0, 0);
        Title = new QLabel(TitleBar);
        Title->setObjectName(QString::fromUtf8("Title"));
        Title->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(Title);


        verticalLayout->addWidget(TitleBar);

        widget_4 = new QWidget(widget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setMinimumSize(QSize(0, 0));
        widget_4->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_2 = new QGridLayout(widget_4);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        WGDashBoard = new DashBoard(widget_4);
        WGDashBoard->setObjectName(QString::fromUtf8("WGDashBoard"));
        WGDashBoard->setMinimumSize(QSize(170, 170));
        WGDashBoard->setMaximumSize(QSize(170, 170));

        gridLayout_2->addWidget(WGDashBoard, 0, 0, 1, 1);


        verticalLayout->addWidget(widget_4);


        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(ThermalMonitor);

        QMetaObject::connectSlotsByName(ThermalMonitor);
    } // setupUi

    void retranslateUi(QWidget *ThermalMonitor)
    {
        ThermalMonitor->setWindowTitle(QCoreApplication::translate("ThermalMonitor", "Form", nullptr));
        widget->setProperty("XUIStyleClass", QVariant(QCoreApplication::translate("ThermalMonitor", "Content", nullptr)));
        widget->setProperty("XUIRound", QVariant(QCoreApplication::translate("ThermalMonitor", "SmallRound", nullptr)));
        TitleBar->setProperty("XUIStyleClass", QVariant(QCoreApplication::translate("ThermalMonitor", "TitleBar", nullptr)));
        Title->setText(QCoreApplication::translate("ThermalMonitor", "TextLabel", nullptr));
        Title->setProperty("XUIFont", QVariant(QCoreApplication::translate("ThermalMonitor", "Medium", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class ThermalMonitor: public Ui_ThermalMonitor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THERMALMONITOR_H
