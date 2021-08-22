/********************************************************************************
** Form generated from reading UI file 'pagetest.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGETEST_H
#define UI_PAGETEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "ctlbtnbox.h"
#include "itemlistbox.h"
#include "thermalmonitor.h"

QT_BEGIN_NAMESPACE

class Ui_PageTest
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    ThermalMonitor *CPUThermal;
    ThermalMonitor *GPUThermal;
    QSpacerItem *verticalSpacer;
    QWidget *widget_3;
    QGridLayout *gridLayout_2;
    QTextEdit *TEMsg;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout;
    ItemListBox *TWItemList;
    CtlBtnBox *widget_5;

    void setupUi(QWidget *PageTest)
    {
        if (PageTest->objectName().isEmpty())
            PageTest->setObjectName(QString::fromUtf8("PageTest"));
        PageTest->resize(1409, 950);
        gridLayout = new QGridLayout(PageTest);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(PageTest);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(15);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(15, 15, 15, 15);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setSpacing(30);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        CPUThermal = new ThermalMonitor(widget_2);
        CPUThermal->setObjectName(QString::fromUtf8("CPUThermal"));
        CPUThermal->setMinimumSize(QSize(200, 200));
        CPUThermal->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_2->addWidget(CPUThermal);

        GPUThermal = new ThermalMonitor(widget_2);
        GPUThermal->setObjectName(QString::fromUtf8("GPUThermal"));
        GPUThermal->setMinimumSize(QSize(200, 200));

        verticalLayout_2->addWidget(GPUThermal);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout->addWidget(widget_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        gridLayout_2 = new QGridLayout(widget_3);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        TEMsg = new QTextEdit(widget_3);
        TEMsg->setObjectName(QString::fromUtf8("TEMsg"));
        TEMsg->setReadOnly(true);

        gridLayout_2->addWidget(TEMsg, 0, 0, 1, 1);


        horizontalLayout->addWidget(widget_3);

        widget_4 = new QWidget(widget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setMinimumSize(QSize(400, 0));
        widget_4->setMaximumSize(QSize(500, 16777215));
        verticalLayout = new QVBoxLayout(widget_4);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        TWItemList = new ItemListBox(widget_4);
        TWItemList->setObjectName(QString::fromUtf8("TWItemList"));

        verticalLayout->addWidget(TWItemList);

        widget_5 = new CtlBtnBox(widget_4);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setMinimumSize(QSize(0, 185));
        widget_5->setMaximumSize(QSize(16777215, 185));

        verticalLayout->addWidget(widget_5);


        horizontalLayout->addWidget(widget_4);


        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(PageTest);

        QMetaObject::connectSlotsByName(PageTest);
    } // setupUi

    void retranslateUi(QWidget *PageTest)
    {
        PageTest->setWindowTitle(QCoreApplication::translate("PageTest", "Form", nullptr));
        //TEMsg->setMarkdown(QString());
        TEMsg->setHtml(QCoreApplication::translate("PageTest", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Cantarell'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        TEMsg->setProperty("XUIStyleClass", QVariant(QCoreApplication::translate("PageTest", "Content", nullptr)));
        TEMsg->setProperty("XUIFont", QVariant(QCoreApplication::translate("PageTest", "Large", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class PageTest: public Ui_PageTest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGETEST_H
