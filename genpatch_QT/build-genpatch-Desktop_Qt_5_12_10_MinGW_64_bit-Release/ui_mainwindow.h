/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *SrcPathButton;
    QPushButton *ProcButton;
    QPushButton *DstPathButton;
    QLabel *label;
    QTextBrowser *LogText;
    QLabel *label_2;
    QLineEdit *SrcPathText;
    QLineEdit *DstPathText;
    QPlainTextEdit *FileText;
    QLabel *label_3;
    QLabel *label_4;
    QStatusBar *statusbar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 561);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        SrcPathButton = new QPushButton(centralwidget);
        SrcPathButton->setObjectName(QString::fromUtf8("SrcPathButton"));
        SrcPathButton->setGeometry(QRect(30, 50, 75, 23));
        ProcButton = new QPushButton(centralwidget);
        ProcButton->setObjectName(QString::fromUtf8("ProcButton"));
        ProcButton->setGeometry(QRect(360, 490, 75, 23));
        DstPathButton = new QPushButton(centralwidget);
        DstPathButton->setObjectName(QString::fromUtf8("DstPathButton"));
        DstPathButton->setGeometry(QRect(30, 110, 75, 23));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(180, 440, 54, 12));
        LogText = new QTextBrowser(centralwidget);
        LogText->setObjectName(QString::fromUtf8("LogText"));
        LogText->setGeometry(QRect(420, 170, 311, 261));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(550, 440, 54, 12));
        SrcPathText = new QLineEdit(centralwidget);
        SrcPathText->setObjectName(QString::fromUtf8("SrcPathText"));
        SrcPathText->setGeometry(QRect(110, 50, 631, 21));
        DstPathText = new QLineEdit(centralwidget);
        DstPathText->setObjectName(QString::fromUtf8("DstPathText"));
        DstPathText->setGeometry(QRect(110, 110, 631, 21));
        FileText = new QPlainTextEdit(centralwidget);
        FileText->setObjectName(QString::fromUtf8("FileText"));
        FileText->setGeometry(QRect(60, 170, 321, 261));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(700, 480, 81, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(700, 500, 71, 16));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        SrcPathButton->setText(QApplication::translate("MainWindow", "\350\276\223\345\205\245\350\267\257\345\276\204", nullptr));
        ProcButton->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        DstPathButton->setText(QApplication::translate("MainWindow", "\350\276\223\345\207\272\350\267\257\345\276\204", nullptr));
        label->setText(QApplication::translate("MainWindow", "File List", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\350\276\223\345\207\272log", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Made by Gary", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Version 0.9", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
