/********************************************************************************
** Form generated from reading UI file 'pagetoolboxes.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGETOOLBOXES_H
#define UI_PAGETOOLBOXES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PageToolboxes
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QPushButton *pushButton;

    void setupUi(QWidget *PageToolboxes)
    {
        if (PageToolboxes->objectName().isEmpty())
            PageToolboxes->setObjectName(QString::fromUtf8("PageToolboxes"));
        PageToolboxes->resize(1192, 812);
        verticalLayout = new QVBoxLayout(PageToolboxes);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(PageToolboxes);
        widget->setObjectName(QString::fromUtf8("widget"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 30, 251, 51));

        verticalLayout->addWidget(widget);


        retranslateUi(PageToolboxes);

        QMetaObject::connectSlotsByName(PageToolboxes);
    } // setupUi

    void retranslateUi(QWidget *PageToolboxes)
    {
        PageToolboxes->setWindowTitle(QCoreApplication::translate("PageToolboxes", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("PageToolboxes", "\346\234\254\346\234\272\347\211\210\346\234\254\344\277\241\346\201\257\344\270\212\344\274\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageToolboxes: public Ui_PageToolboxes {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGETOOLBOXES_H
