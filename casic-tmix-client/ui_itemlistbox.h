/********************************************************************************
** Form generated from reading UI file 'itemlistbox.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITEMLISTBOX_H
#define UI_ITEMLISTBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ItemListBox
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
    QTableWidget *TWItemList;

    void setupUi(QWidget *ItemListBox)
    {
        if (ItemListBox->objectName().isEmpty())
            ItemListBox->setObjectName(QString::fromUtf8("ItemListBox"));
        ItemListBox->resize(416, 597);
        gridLayout = new QGridLayout(ItemListBox);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(ItemListBox);
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
        gridLayout_2->setContentsMargins(10, 0, 0, 0);
        TWItemList = new QTableWidget(widget_4);
        if (TWItemList->columnCount() < 4)
            TWItemList->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        TWItemList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        TWItemList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        TWItemList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        TWItemList->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        TWItemList->setObjectName(QString::fromUtf8("TWItemList"));
        TWItemList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        TWItemList->horizontalHeader()->setVisible(true);
        TWItemList->horizontalHeader()->setStretchLastSection(true);
        TWItemList->verticalHeader()->setVisible(false);

        gridLayout_2->addWidget(TWItemList, 0, 0, 1, 1);


        verticalLayout->addWidget(widget_4);


        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(ItemListBox);

        QMetaObject::connectSlotsByName(ItemListBox);
    } // setupUi

    void retranslateUi(QWidget *ItemListBox)
    {
        ItemListBox->setWindowTitle(QCoreApplication::translate("ItemListBox", "Form", nullptr));
        widget->setProperty("XUIStyleClass", QVariant(QCoreApplication::translate("ItemListBox", "Content", nullptr)));
        widget->setProperty("XUIRound", QVariant(QCoreApplication::translate("ItemListBox", "SmallRound", nullptr)));
        TitleBar->setProperty("XUIStyleClass", QVariant(QCoreApplication::translate("ItemListBox", "TitleBar", nullptr)));
        Title->setText(QCoreApplication::translate("ItemListBox", "\346\265\213\350\257\225\351\241\271\345\210\227\350\241\250", nullptr));
        Title->setProperty("XUIFont", QVariant(QCoreApplication::translate("ItemListBox", "Medium", nullptr)));
        QTableWidgetItem *___qtablewidgetitem = TWItemList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ItemListBox", "\347\274\226\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = TWItemList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ItemListBox", "\346\265\213\350\257\225\351\241\271", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = TWItemList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ItemListBox", "\346\265\213\350\257\225\346\240\207\345\207\206", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = TWItemList->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ItemListBox", "\346\265\213\350\257\225\347\273\223\346\236\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ItemListBox: public Ui_ItemListBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ITEMLISTBOX_H
