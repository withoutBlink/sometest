/********************************************************************************
** Form generated from reading UI file 'pagejournal.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGEJOURNAL_H
#define UI_PAGEJOURNAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PageJournal
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QTableWidget *tableWidget;

    void setupUi(QWidget *PageJournal)
    {
        if (PageJournal->objectName().isEmpty())
            PageJournal->setObjectName(QString::fromUtf8("PageJournal"));
        PageJournal->resize(1330, 940);
        gridLayout = new QGridLayout(PageJournal);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(PageJournal);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        tableWidget = new QTableWidget(widget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout_2->addWidget(tableWidget, 0, 0, 1, 1);


        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(PageJournal);

        QMetaObject::connectSlotsByName(PageJournal);
    } // setupUi

    void retranslateUi(QWidget *PageJournal)
    {
        PageJournal->setWindowTitle(QCoreApplication::translate("PageJournal", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageJournal: public Ui_PageJournal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGEJOURNAL_H
