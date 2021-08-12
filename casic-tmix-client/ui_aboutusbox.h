/********************************************************************************
** Form generated from reading UI file 'aboutusbox.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTUSBOX_H
#define UI_ABOUTUSBOX_H

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

class Ui_AboutUSBox
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *WGBackGround;
    QVBoxLayout *verticalLayout_2;
    QWidget *TitleBar;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLabel *label;
    QPushButton *pushButton_3;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_7;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *Software;
    QLabel *Version;
    QLabel *RegisterFrom;
    QLabel *Copyright;

    void setupUi(QDialog *AboutUSBox)
    {
        if (AboutUSBox->objectName().isEmpty())
            AboutUSBox->setObjectName(QString::fromUtf8("AboutUSBox"));
        AboutUSBox->resize(765, 296);
        verticalLayout = new QVBoxLayout(AboutUSBox);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        WGBackGround = new QWidget(AboutUSBox);
        WGBackGround->setObjectName(QString::fromUtf8("WGBackGround"));
        verticalLayout_2 = new QVBoxLayout(WGBackGround);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        TitleBar = new QWidget(WGBackGround);
        TitleBar->setObjectName(QString::fromUtf8("TitleBar"));
        TitleBar->setMinimumSize(QSize(0, 55));
        TitleBar->setMaximumSize(QSize(16777215, 55));
        horizontalLayout = new QHBoxLayout(TitleBar);
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(15, 0, 5, 0);
        label_2 = new QLabel(TitleBar);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(16, 16));
        label_2->setMaximumSize(QSize(16, 16));
        label_2->setStyleSheet(QString::fromUtf8("image: url(:/static/images/icon_aboutus_act.svg);"));

        horizontalLayout->addWidget(label_2);

        label = new QLabel(TitleBar);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        pushButton_3 = new QPushButton(TitleBar);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(55, 55));
        pushButton_3->setMaximumSize(QSize(55, 55));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/static/images/icon_close.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_3->setIcon(icon);

        horizontalLayout->addWidget(pushButton_3);


        verticalLayout_2->addWidget(TitleBar);

        widget_3 = new QWidget(WGBackGround);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setSpacing(20);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(50, -1, -1, 25);
        widget_5 = new QWidget(widget_3);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setMinimumSize(QSize(200, 0));
        widget_5->setMaximumSize(QSize(200, 16777215));
        verticalLayout_4 = new QVBoxLayout(widget_5);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 30);
        label_7 = new QLabel(widget_5);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(200, 120));
        label_7->setMaximumSize(QSize(200, 120));
        label_7->setStyleSheet(QString::fromUtf8("image: url(:/static/images/icon_706.png);"));
        label_7->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_4->addWidget(label_7);


        horizontalLayout_2->addWidget(widget_5);

        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        verticalLayout_3 = new QVBoxLayout(widget_4);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        Software = new QLabel(widget_4);
        Software->setObjectName(QString::fromUtf8("Software"));

        verticalLayout_3->addWidget(Software);

        Version = new QLabel(widget_4);
        Version->setObjectName(QString::fromUtf8("Version"));

        verticalLayout_3->addWidget(Version);

        RegisterFrom = new QLabel(widget_4);
        RegisterFrom->setObjectName(QString::fromUtf8("RegisterFrom"));

        verticalLayout_3->addWidget(RegisterFrom);


        horizontalLayout_2->addWidget(widget_4);


        verticalLayout_2->addWidget(widget_3);

        Copyright = new QLabel(WGBackGround);
        Copyright->setObjectName(QString::fromUtf8("Copyright"));
        Copyright->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(Copyright);


        verticalLayout->addWidget(WGBackGround);


        retranslateUi(AboutUSBox);

        QMetaObject::connectSlotsByName(AboutUSBox);
    } // setupUi

    void retranslateUi(QDialog *AboutUSBox)
    {
        AboutUSBox->setWindowTitle(QCoreApplication::translate("AboutUSBox", "Dialog", nullptr));
        label_2->setText(QString());
        label->setText(QCoreApplication::translate("AboutUSBox", "\345\205\263\344\272\216\346\210\221\344\273\254", nullptr));
        label->setProperty("XUIStyleClass", QVariant(QCoreApplication::translate("AboutUSBox", "Title", nullptr)));
        pushButton_3->setText(QString());
        pushButton_3->setProperty("XUIStyleClass", QVariant(QCoreApplication::translate("AboutUSBox", "BtnClose", nullptr)));
        label_7->setText(QCoreApplication::translate("AboutUSBox", "\350\210\252\345\244\251\344\270\203\343\200\207\345\205\255", nullptr));
        Software->setText(QCoreApplication::translate("AboutUSBox", "T-Mix", nullptr));
        Software->setProperty("XUIFont", QVariant(QCoreApplication::translate("AboutUSBox", "Large", nullptr)));
        Version->setText(QCoreApplication::translate("AboutUSBox", "\347\211\210\346\234\254\357\274\232V3.0.1", nullptr));
        Version->setProperty("XUIFont", QVariant(QCoreApplication::translate("AboutUSBox", "Medium", nullptr)));
        RegisterFrom->setText(QCoreApplication::translate("AboutUSBox", "\346\263\250\345\206\214\357\274\232\350\201\224\350\276\276", nullptr));
        RegisterFrom->setProperty("XUIFont", QVariant(QCoreApplication::translate("AboutUSBox", "Medium", nullptr)));
        Copyright->setText(QCoreApplication::translate("AboutUSBox", "Copyright\302\251 2021 \345\214\227\344\272\254\350\256\241\347\256\227\346\234\272\346\212\200\346\234\257\345\217\212\345\272\224\347\224\250\347\240\224\347\251\266\346\211\200", nullptr));
        Copyright->setProperty("XUIFont", QVariant(QCoreApplication::translate("AboutUSBox", "Mini", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class AboutUSBox: public Ui_AboutUSBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTUSBOX_H
