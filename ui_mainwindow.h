/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *btnLire;
    QPushButton *btnArreter;
    QSpinBox *spinBoxTempo;
    QPushButton *btnSelectPattern;
    QLineEdit *lineEditFile;
    QPushButton *btnQuitter;
    QLabel *label;
    QSlider *sliderProgression;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(502, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        btnLire = new QPushButton(centralWidget);
        btnLire->setObjectName(QStringLiteral("btnLire"));
        btnLire->setGeometry(QRect(20, 60, 141, 71));
        btnArreter = new QPushButton(centralWidget);
        btnArreter->setObjectName(QStringLiteral("btnArreter"));
        btnArreter->setGeometry(QRect(180, 60, 141, 71));
        spinBoxTempo = new QSpinBox(centralWidget);
        spinBoxTempo->setObjectName(QStringLiteral("spinBoxTempo"));
        spinBoxTempo->setGeometry(QRect(420, 80, 61, 31));
        spinBoxTempo->setMinimum(40);
        spinBoxTempo->setMaximum(999);
        spinBoxTempo->setSingleStep(5);
        btnSelectPattern = new QPushButton(centralWidget);
        btnSelectPattern->setObjectName(QStringLiteral("btnSelectPattern"));
        btnSelectPattern->setGeometry(QRect(390, 10, 75, 31));
        lineEditFile = new QLineEdit(centralWidget);
        lineEditFile->setObjectName(QStringLiteral("lineEditFile"));
        lineEditFile->setGeometry(QRect(20, 10, 351, 20));
        lineEditFile->setReadOnly(true);
        btnQuitter = new QPushButton(centralWidget);
        btnQuitter->setObjectName(QStringLiteral("btnQuitter"));
        btnQuitter->setGeometry(QRect(410, 210, 75, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(370, 90, 46, 13));
        sliderProgression = new QSlider(centralWidget);
        sliderProgression->setObjectName(QStringLiteral("sliderProgression"));
        sliderProgression->setGeometry(QRect(20, 170, 461, 22));
        sliderProgression->setOrientation(Qt::Horizontal);
        sliderProgression->setTickPosition(QSlider::TicksBothSides);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 502, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        btnLire->setText(QApplication::translate("MainWindow", "LIRE", 0));
        btnArreter->setText(QApplication::translate("MainWindow", "ARRETER", 0));
        spinBoxTempo->setPrefix(QString());
        btnSelectPattern->setText(QApplication::translate("MainWindow", "Choisir...", 0));
        btnQuitter->setText(QApplication::translate("MainWindow", "Quitter", 0));
        label->setText(QApplication::translate("MainWindow", "Tempo", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
