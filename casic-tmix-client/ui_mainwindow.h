/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "pagehome.h"
#include "pagejournal.h"
#include "pagetest.h"
#include "pagetoolboxes.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *WGBackGround;
    QVBoxLayout *verticalLayout;
    QWidget *TitleBar;
    QHBoxLayout *horizontalLayout_2;
    QLabel *LBLogo;
    QLabel *LBTitle;
    QPushButton *BtnAboutUS;
    QPushButton *BtnMinimized;
    QPushButton *BtnMaximized;
    QPushButton *BtnClose;
    QStackedWidget *SWBodyPages;
    QWidget *MainPage;
    QVBoxLayout *verticalLayout_2;
    QStackedWidget *SWBallotView;
    PageHome *WGHomeView;
    PageToolboxes *WGToolBoxes;
    PageJournal *WGLogView;
    QWidget *ToolBtnboxes;
    QHBoxLayout *horizontalLayout;
    QPushButton *BtnHome;
    QPushButton *BtnToolBox;
    QPushButton *BtnLogs;
    QSpacerItem *horizontalSpacer;
    PageTest *TestPage;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1185, 736);
        WGBackGround = new QWidget(MainWindow);
        WGBackGround->setObjectName(QString::fromUtf8("WGBackGround"));
        WGBackGround->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(WGBackGround);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        TitleBar = new QWidget(WGBackGround);
        TitleBar->setObjectName(QString::fromUtf8("TitleBar"));
        TitleBar->setMinimumSize(QSize(0, 55));
        TitleBar->setMaximumSize(QSize(16777215, 55));
        horizontalLayout_2 = new QHBoxLayout(TitleBar);
        horizontalLayout_2->setSpacing(5);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(15, 0, 5, 0);
        LBLogo = new QLabel(TitleBar);
        LBLogo->setObjectName(QString::fromUtf8("LBLogo"));
        LBLogo->setMinimumSize(QSize(16, 16));
        LBLogo->setMaximumSize(QSize(16, 16));
        LBLogo->setStyleSheet(QString::fromUtf8("image: url(:/static/images/icon_logo.svg);"));

        horizontalLayout_2->addWidget(LBLogo);

        LBTitle = new QLabel(TitleBar);
        LBTitle->setObjectName(QString::fromUtf8("LBTitle"));

        horizontalLayout_2->addWidget(LBTitle);

        BtnAboutUS = new QPushButton(TitleBar);
        BtnAboutUS->setObjectName(QString::fromUtf8("BtnAboutUS"));
        BtnAboutUS->setMinimumSize(QSize(55, 55));
        BtnAboutUS->setMaximumSize(QSize(55, 55));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/static/images/icon_aboutus_def.svg"), QSize(), QIcon::Normal, QIcon::Off);
        BtnAboutUS->setIcon(icon);

        horizontalLayout_2->addWidget(BtnAboutUS);

        BtnMinimized = new QPushButton(TitleBar);
        BtnMinimized->setObjectName(QString::fromUtf8("BtnMinimized"));
        BtnMinimized->setMinimumSize(QSize(55, 55));
        BtnMinimized->setMaximumSize(QSize(55, 55));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/static/images/icon_min.svg"), QSize(), QIcon::Normal, QIcon::Off);
        BtnMinimized->setIcon(icon1);

        horizontalLayout_2->addWidget(BtnMinimized);

        BtnMaximized = new QPushButton(TitleBar);
        BtnMaximized->setObjectName(QString::fromUtf8("BtnMaximized"));
        BtnMaximized->setMinimumSize(QSize(55, 55));
        BtnMaximized->setMaximumSize(QSize(55, 55));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/static/images/icon_max.svg"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/static/images/icon_restore.svg"), QSize(), QIcon::Active, QIcon::On);
        icon2.addFile(QString::fromUtf8(":/static/images/icon_restore.svg"), QSize(), QIcon::Selected, QIcon::On);
        BtnMaximized->setIcon(icon2);
        BtnMaximized->setCheckable(true);

        horizontalLayout_2->addWidget(BtnMaximized);

        BtnClose = new QPushButton(TitleBar);
        BtnClose->setObjectName(QString::fromUtf8("BtnClose"));
        BtnClose->setMinimumSize(QSize(55, 55));
        BtnClose->setMaximumSize(QSize(55, 55));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/static/images/icon_close.svg"), QSize(), QIcon::Normal, QIcon::Off);
        BtnClose->setIcon(icon3);

        horizontalLayout_2->addWidget(BtnClose);


        verticalLayout->addWidget(TitleBar);

        SWBodyPages = new QStackedWidget(WGBackGround);
        SWBodyPages->setObjectName(QString::fromUtf8("SWBodyPages"));
        MainPage = new QWidget();
        MainPage->setObjectName(QString::fromUtf8("MainPage"));
        verticalLayout_2 = new QVBoxLayout(MainPage);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        SWBallotView = new QStackedWidget(MainPage);
        SWBallotView->setObjectName(QString::fromUtf8("SWBallotView"));
        WGHomeView = new PageHome();
        WGHomeView->setObjectName(QString::fromUtf8("WGHomeView"));
        SWBallotView->addWidget(WGHomeView);
        WGToolBoxes = new PageToolboxes();
        WGToolBoxes->setObjectName(QString::fromUtf8("WGToolBoxes"));
        SWBallotView->addWidget(WGToolBoxes);
        WGLogView = new PageJournal();
        WGLogView->setObjectName(QString::fromUtf8("WGLogView"));
        SWBallotView->addWidget(WGLogView);

        verticalLayout_2->addWidget(SWBallotView);

        ToolBtnboxes = new QWidget(MainPage);
        ToolBtnboxes->setObjectName(QString::fromUtf8("ToolBtnboxes"));
        ToolBtnboxes->setMinimumSize(QSize(0, 135));
        ToolBtnboxes->setMaximumSize(QSize(16777215, 135));
        horizontalLayout = new QHBoxLayout(ToolBtnboxes);
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        BtnHome = new QPushButton(ToolBtnboxes);
        BtnHome->setObjectName(QString::fromUtf8("BtnHome"));
        BtnHome->setMinimumSize(QSize(200, 135));
        BtnHome->setMaximumSize(QSize(200, 135));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/static/images/icon_home_def.svg"), QSize(), QIcon::Normal, QIcon::Off);
        icon4.addFile(QString::fromUtf8(":/static/images/icon_home_act.svg"), QSize(), QIcon::Active, QIcon::Off);
        icon4.addFile(QString::fromUtf8(":/static/images/icon_home_act.svg"), QSize(), QIcon::Active, QIcon::On);
        BtnHome->setIcon(icon4);
        BtnHome->setCheckable(true);
        BtnHome->setChecked(true);
        BtnHome->setAutoExclusive(true);

        horizontalLayout->addWidget(BtnHome);

        BtnToolBox = new QPushButton(ToolBtnboxes);
        BtnToolBox->setObjectName(QString::fromUtf8("BtnToolBox"));
        BtnToolBox->setMinimumSize(QSize(200, 135));
        BtnToolBox->setMaximumSize(QSize(200, 135));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/static/images/icon_toolbox_def.svg"), QSize(), QIcon::Normal, QIcon::Off);
        icon5.addFile(QString::fromUtf8(":/static/images/icon_toolbox_act.svg"), QSize(), QIcon::Active, QIcon::Off);
        icon5.addFile(QString::fromUtf8(":/static/images/icon_toolbox_act.svg"), QSize(), QIcon::Active, QIcon::On);
        BtnToolBox->setIcon(icon5);
        BtnToolBox->setCheckable(true);
        BtnToolBox->setAutoExclusive(true);

        horizontalLayout->addWidget(BtnToolBox);

        BtnLogs = new QPushButton(ToolBtnboxes);
        BtnLogs->setObjectName(QString::fromUtf8("BtnLogs"));
        BtnLogs->setMinimumSize(QSize(200, 135));
        BtnLogs->setMaximumSize(QSize(200, 135));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/static/images/icon_logs_def.svg"), QSize(), QIcon::Normal, QIcon::Off);
        icon6.addFile(QString::fromUtf8(":/static/images/icon_logs_act.svg"), QSize(), QIcon::Active, QIcon::Off);
        icon6.addFile(QString::fromUtf8(":/static/images/icon_logs_act.svg"), QSize(), QIcon::Active, QIcon::On);
        BtnLogs->setIcon(icon6);
        BtnLogs->setCheckable(true);
        BtnLogs->setAutoExclusive(true);

        horizontalLayout->addWidget(BtnLogs);

        horizontalSpacer = new QSpacerItem(562, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addWidget(ToolBtnboxes);

        SWBodyPages->addWidget(MainPage);
        TestPage = new PageTest();
        TestPage->setObjectName(QString::fromUtf8("TestPage"));
        SWBodyPages->addWidget(TestPage);

        verticalLayout->addWidget(SWBodyPages);

        MainWindow->setCentralWidget(WGBackGround);

        retranslateUi(MainWindow);

        SWBodyPages->setCurrentIndex(1);
        SWBallotView->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        WGBackGround->setProperty("XUIStyleClass", QVariant(QCoreApplication::translate("MainWindow", "Body", nullptr)));
        LBLogo->setText(QString());
        LBTitle->setText(QCoreApplication::translate("MainWindow", "T-Mix", nullptr));
        LBTitle->setProperty("XUIStyleClass", QVariant(QCoreApplication::translate("MainWindow", "Title", nullptr)));
#if QT_CONFIG(tooltip)
        BtnAboutUS->setToolTip(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216\346\210\221\344\273\254", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnAboutUS->setText(QString());
#if QT_CONFIG(tooltip)
        BtnMinimized->setToolTip(QCoreApplication::translate("MainWindow", "\346\234\200\345\260\217\345\214\226", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnMinimized->setText(QString());
#if QT_CONFIG(tooltip)
        BtnMaximized->setToolTip(QCoreApplication::translate("MainWindow", "\346\234\200\345\244\247\345\214\226", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnMaximized->setText(QString());
#if QT_CONFIG(tooltip)
        BtnClose->setToolTip(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\347\250\213\345\272\217", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnClose->setText(QString());
        BtnClose->setProperty("XUIBtn", QVariant(QCoreApplication::translate("MainWindow", "BtnClose", nullptr)));
        ToolBtnboxes->setProperty("XUIStyleClass", QVariant(QCoreApplication::translate("MainWindow", "Content", nullptr)));
        BtnHome->setText(QCoreApplication::translate("MainWindow", "\345\274\225\345\257\274\346\265\213\350\257\225", nullptr));
        BtnHome->setProperty("XUIBtn", QVariant(QCoreApplication::translate("MainWindow", "BtnMenu", nullptr)));
        BtnToolBox->setText(QCoreApplication::translate("MainWindow", "\345\267\245\345\205\267\347\256\261", nullptr));
        BtnToolBox->setProperty("XUIBtn", QVariant(QCoreApplication::translate("MainWindow", "BtnMenu", nullptr)));
        BtnLogs->setText(QCoreApplication::translate("MainWindow", "\346\265\213\350\257\225\350\256\260\345\275\225", nullptr));
        BtnLogs->setProperty("XUIBtn", QVariant(QCoreApplication::translate("MainWindow", "BtnMenu", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
