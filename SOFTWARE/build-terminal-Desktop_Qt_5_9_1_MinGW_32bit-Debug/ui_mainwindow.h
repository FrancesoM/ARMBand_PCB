/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionAboutQt;
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionConfigure;
    QAction *actionClear;
    QAction *actionQuit;
    QAction *actionConnectGyro;
    QAction *actionDisconnectGyro;
    QAction *actionConfigureGyro;
    QAction *actionTranslate;
    QWidget *mainLayout;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *GraphLayoutPlaceHolder;
    QHBoxLayout *TwoGraphsLayout;
    QMenuBar *menuBar;
    QMenu *menuCalls;
    QMenu *menuTools;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(781, 579);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionAboutQt = new QAction(MainWindow);
        actionAboutQt->setObjectName(QStringLiteral("actionAboutQt"));
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConnect->setIcon(icon);
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/disconnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDisconnect->setIcon(icon1);
        actionConfigure = new QAction(MainWindow);
        actionConfigure->setObjectName(QStringLiteral("actionConfigure"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/UHSett.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionConfigure->setIcon(icon2);
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClear->setIcon(icon3);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/application-exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon4);
        actionConnectGyro = new QAction(MainWindow);
        actionConnectGyro->setObjectName(QStringLiteral("actionConnectGyro"));
        actionConnectGyro->setIcon(icon);
        actionDisconnectGyro = new QAction(MainWindow);
        actionDisconnectGyro->setObjectName(QStringLiteral("actionDisconnectGyro"));
        actionDisconnectGyro->setIcon(icon1);
        actionConfigureGyro = new QAction(MainWindow);
        actionConfigureGyro->setObjectName(QStringLiteral("actionConfigureGyro"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/GyroSett.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionConfigureGyro->setIcon(icon5);
        actionTranslate = new QAction(MainWindow);
        actionTranslate->setObjectName(QStringLiteral("actionTranslate"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images/tra.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTranslate->setIcon(icon6);
        mainLayout = new QWidget(MainWindow);
        mainLayout->setObjectName(QStringLiteral("mainLayout"));
        verticalLayout = new QVBoxLayout(mainLayout);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        GraphLayoutPlaceHolder = new QVBoxLayout();
        GraphLayoutPlaceHolder->setSpacing(6);
        GraphLayoutPlaceHolder->setObjectName(QStringLiteral("GraphLayoutPlaceHolder"));
        TwoGraphsLayout = new QHBoxLayout();
        TwoGraphsLayout->setSpacing(6);
        TwoGraphsLayout->setObjectName(QStringLiteral("TwoGraphsLayout"));

        GraphLayoutPlaceHolder->addLayout(TwoGraphsLayout);


        verticalLayout->addLayout(GraphLayoutPlaceHolder);

        MainWindow->setCentralWidget(mainLayout);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 781, 20));
        menuCalls = new QMenu(menuBar);
        menuCalls->setObjectName(QStringLiteral("menuCalls"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuCalls->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuCalls->addAction(actionConnect);
        menuCalls->addAction(actionDisconnect);
        menuCalls->addAction(actionConnectGyro);
        menuCalls->addAction(actionDisconnectGyro);
        menuCalls->addSeparator();
        menuCalls->addAction(actionQuit);
        menuTools->addAction(actionConfigure);
        menuTools->addAction(actionConfigureGyro);
        menuTools->addAction(actionClear);
        menuTools->addAction(actionTranslate);
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionAboutQt);
        mainToolBar->addAction(actionConnect);
        mainToolBar->addAction(actionDisconnect);
        mainToolBar->addAction(actionConfigure);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionConnectGyro);
        mainToolBar->addAction(actionDisconnectGyro);
        mainToolBar->addAction(actionConfigureGyro);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionClear);
        mainToolBar->addAction(actionTranslate);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Simple Terminal", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("MainWindow", "&About", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionAbout->setToolTip(QApplication::translate("MainWindow", "About program", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionAbout->setShortcut(QApplication::translate("MainWindow", "Alt+A", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionAboutQt->setText(QApplication::translate("MainWindow", "About Qt", Q_NULLPTR));
        actionConnect->setText(QApplication::translate("MainWindow", "C&onnect", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionConnect->setToolTip(QApplication::translate("MainWindow", "Connect to serial port", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionConnect->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionDisconnect->setText(QApplication::translate("MainWindow", "&Disconnect", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionDisconnect->setToolTip(QApplication::translate("MainWindow", "Disconnect from serial port", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionDisconnect->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionConfigure->setText(QApplication::translate("MainWindow", "&Configure", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionConfigure->setToolTip(QApplication::translate("MainWindow", "Configure serial port", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionConfigure->setShortcut(QApplication::translate("MainWindow", "Alt+C", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionClear->setText(QApplication::translate("MainWindow", "C&lear", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionClear->setToolTip(QApplication::translate("MainWindow", "Clear data", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionClear->setShortcut(QApplication::translate("MainWindow", "Alt+L", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionQuit->setText(QApplication::translate("MainWindow", "&Quit", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionConnectGyro->setText(QApplication::translate("MainWindow", "Connect Gyro", Q_NULLPTR));
        actionDisconnectGyro->setText(QApplication::translate("MainWindow", "Disconnect Gyro", Q_NULLPTR));
        actionConfigureGyro->setText(QApplication::translate("MainWindow", "Configure Gyro", Q_NULLPTR));
        actionTranslate->setText(QApplication::translate("MainWindow", "Translate", Q_NULLPTR));
        menuCalls->setTitle(QApplication::translate("MainWindow", "Calls", Q_NULLPTR));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
