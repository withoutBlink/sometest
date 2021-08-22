/********************************************************************************
** Form generated from reading UI file 'pagehome.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGEHOME_H
#define UI_PAGEHOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PageHome
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QLabel *LBHomeText;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *BtnStarted;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *PageHome)
    {
        if (PageHome->objectName().isEmpty())
            PageHome->setObjectName(QString::fromUtf8("PageHome"));
        PageHome->resize(1050, 636);
        gridLayout = new QGridLayout(PageHome);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(PageHome);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        LBHomeText = new QLabel(widget);
        LBHomeText->setObjectName(QString::fromUtf8("LBHomeText"));
        LBHomeText->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(LBHomeText);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        BtnStarted = new QPushButton(widget);
        BtnStarted->setObjectName(QString::fromUtf8("BtnStarted"));
        BtnStarted->setMinimumSize(QSize(215, 75));
        BtnStarted->setMaximumSize(QSize(215, 75));

        horizontalLayout_2->addWidget(BtnStarted);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(PageHome);

        QMetaObject::connectSlotsByName(PageHome);
    } // setupUi

    void retranslateUi(QWidget *PageHome)
    {
        PageHome->setWindowTitle(QCoreApplication::translate("PageHome", "Form", nullptr));
        LBHomeText->setText(QCoreApplication::translate("PageHome", "\350\256\251\346\265\213\350\257\225\346\233\264\347\256\200\345\215\225\343\200\201\346\233\264\345\277\253\346\215\267", nullptr));
        LBHomeText->setProperty("XUIFont", QVariant(QCoreApplication::translate("PageHome", "ExtraLarge", nullptr)));
        BtnStarted->setText(QCoreApplication::translate("PageHome", "\345\274\225\345\257\274\346\265\213\350\257\225", nullptr));
        BtnStarted->setProperty("XUIFont", QVariant(QCoreApplication::translate("PageHome", "Large", nullptr)));
        BtnStarted->setProperty("XUIRound", QVariant(QCoreApplication::translate("PageHome", "LargeRound", nullptr)));
        BtnStarted->setProperty("XUIStyleClass", QVariant(QCoreApplication::translate("PageHome", "BtnStart", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class PageHome: public Ui_PageHome {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGEHOME_H
