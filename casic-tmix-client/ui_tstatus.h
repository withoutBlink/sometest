/********************************************************************************
** Form generated from reading UI file 'tstatus.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TSTATUS_H
#define UI_TSTATUS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TStatus
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *LBStatus;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *TStatus)
    {
        if (TStatus->objectName().isEmpty())
            TStatus->setObjectName(QString::fromUtf8("TStatus"));
        TStatus->resize(876, 173);
        horizontalLayout = new QHBoxLayout(TStatus);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        LBStatus = new QLabel(TStatus);
        LBStatus->setObjectName(QString::fromUtf8("LBStatus"));
        LBStatus->setMinimumSize(QSize(55, 25));
        LBStatus->setMaximumSize(QSize(55, 25));
        LBStatus->setAlignment(Qt::AlignCenter);
        LBStatus->setProperty("XUIStatus", QVariant(0u));

        horizontalLayout->addWidget(LBStatus);

        horizontalSpacer_2 = new QSpacerItem(392, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        retranslateUi(TStatus);

        QMetaObject::connectSlotsByName(TStatus);
    } // setupUi

    void retranslateUi(QWidget *TStatus)
    {
        TStatus->setWindowTitle(QCoreApplication::translate("TStatus", "Form", nullptr));
        LBStatus->setText(QCoreApplication::translate("TStatus", "\345\276\205\346\265\213\350\257\225", nullptr));
        LBStatus->setProperty("XUIRound", QVariant(QCoreApplication::translate("TStatus", "MediumRound", nullptr)));
        LBStatus->setProperty("XUIColor", QVariant(QCoreApplication::translate("TStatus", "White", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class TStatus: public Ui_TStatus {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TSTATUS_H
