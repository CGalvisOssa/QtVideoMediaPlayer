/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QWidget *centralwidget;
    QGroupBox *groupBox_Video;
    QPushButton *pushButton_retroceder;
    QSlider *verticalSlider;
    QSlider *progressBar;
    QLabel *label_time;
    QPushButton *pushButton_pausar;
    QPushButton *pushButton_adelantar;
    QPushButton *pushButton_siguiente;
    QPushButton *pushButton_anterior;
    QPushButton *pushButton_mute;
    QPushButton *pushButton_stop;
    QTreeView *treeView;
    QMenuBar *menubar;
    QMenu *menuSelecciona_el_video;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(949, 600);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox_Video = new QGroupBox(centralwidget);
        groupBox_Video->setObjectName("groupBox_Video");
        groupBox_Video->setGeometry(QRect(30, 50, 551, 331));
        groupBox_Video->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 2px solid #2e2e2e;\n"
"    border-radius: 10px;\n"
"    background-color:  rgba(30, 30, 30, 180);\n"
"    margin-top: 0px;\n"
"}\n"
"\n"
""));
        pushButton_retroceder = new QPushButton(centralwidget);
        pushButton_retroceder->setObjectName("pushButton_retroceder");
        pushButton_retroceder->setGeometry(QRect(40, 450, 71, 71));
        pushButton_retroceder->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8e8481;\n"
"    border-radius: 35px;  /* Mitad del tama\303\261o del ancho y alto para hacer un c\303\255rculo */\n"
"    background-color: #938f8e;\n"
"    color: white;\n"
"    width: 50px;  /* Anchura del bot\303\263n */\n"
"    height: 50px; /* Altura del bot\303\263n */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #3e3e3e;  /* Color cuando se presiona */\n"
"}"));
        verticalSlider = new QSlider(centralwidget);
        verticalSlider->setObjectName("verticalSlider");
        verticalSlider->setGeometry(QRect(620, 60, 41, 191));
        verticalSlider->setOrientation(Qt::Orientation::Vertical);
        progressBar = new QSlider(centralwidget);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(100, 390, 431, 41));
        progressBar->setOrientation(Qt::Orientation::Horizontal);
        label_time = new QLabel(centralwidget);
        label_time->setObjectName("label_time");
        label_time->setGeometry(QRect(30, 400, 63, 20));
        QFont font;
        font.setBold(true);
        label_time->setFont(font);
        pushButton_pausar = new QPushButton(centralwidget);
        pushButton_pausar->setObjectName("pushButton_pausar");
        pushButton_pausar->setGeometry(QRect(150, 450, 71, 71));
        pushButton_pausar->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8e8481;\n"
"    border-radius: 35px;  /* Mitad del tama\303\261o del ancho y alto para hacer un c\303\255rculo */\n"
"    background-color: #938f8e;\n"
"    color: white;\n"
"    width: 50px;  /* Anchura del bot\303\263n */\n"
"    height: 50px; /* Altura del bot\303\263n */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #3e3e3e;  /* Color cuando se presiona */\n"
"}"));
        pushButton_adelantar = new QPushButton(centralwidget);
        pushButton_adelantar->setObjectName("pushButton_adelantar");
        pushButton_adelantar->setGeometry(QRect(380, 450, 71, 71));
        pushButton_adelantar->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8e8481;\n"
"    border-radius: 35px;  /* Mitad del tama\303\261o del ancho y alto para hacer un c\303\255rculo */\n"
"    background-color: #938f8e;\n"
"    color: white;\n"
"    width: 50px;  /* Anchura del bot\303\263n */\n"
"    height: 50px; /* Altura del bot\303\263n */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #3e3e3e;  /* Color cuando se presiona */\n"
"}"));
        pushButton_siguiente = new QPushButton(centralwidget);
        pushButton_siguiente->setObjectName("pushButton_siguiente");
        pushButton_siguiente->setGeometry(QRect(610, 450, 71, 71));
        pushButton_siguiente->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8e8481;\n"
"    border-radius: 35px;  /* Mitad del tama\303\261o del ancho y alto para hacer un c\303\255rculo */\n"
"    background-color: #938f8e;\n"
"    color: white;\n"
"    width: 50px;  /* Anchura del bot\303\263n */\n"
"    height: 50px; /* Altura del bot\303\263n */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #3e3e3e;  /* Color cuando se presiona */\n"
"}"));
        pushButton_anterior = new QPushButton(centralwidget);
        pushButton_anterior->setObjectName("pushButton_anterior");
        pushButton_anterior->setGeometry(QRect(490, 450, 71, 71));
        pushButton_anterior->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8e8481;\n"
"    border-radius: 35px;  /* Mitad del tama\303\261o del ancho y alto para hacer un c\303\255rculo */\n"
"    background-color: #938f8e;\n"
"    color: white;\n"
"    width: 50px;  /* Anchura del bot\303\263n */\n"
"    height: 50px; /* Altura del bot\303\263n */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #3e3e3e;  /* Color cuando se presiona */\n"
"}"));
        pushButton_mute = new QPushButton(centralwidget);
        pushButton_mute->setObjectName("pushButton_mute");
        pushButton_mute->setGeometry(QRect(610, 320, 71, 71));
        pushButton_mute->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8e8481;\n"
"    border-radius: 35px;  /* Mitad del tama\303\261o del ancho y alto para hacer un c\303\255rculo */\n"
"    background-color: #938f8e;\n"
"    color: white;\n"
"    width: 50px;  /* Anchura del bot\303\263n */\n"
"    height: 50px; /* Altura del bot\303\263n */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #3e3e3e;  /* Color cuando se presiona */\n"
"}"));
        pushButton_stop = new QPushButton(centralwidget);
        pushButton_stop->setObjectName("pushButton_stop");
        pushButton_stop->setGeometry(QRect(270, 450, 71, 71));
        pushButton_stop->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8e8481;\n"
"    border-radius: 35px;  /* Mitad del tama\303\261o del ancho y alto para hacer un c\303\255rculo */\n"
"    background-color: #938f8e;\n"
"    color: white;\n"
"    width: 50px;  /* Anchura del bot\303\263n */\n"
"    height: 50px; /* Altura del bot\303\263n */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #3e3e3e;  /* Color cuando se presiona */\n"
"}"));
        treeView = new QTreeView(centralwidget);
        treeView->setObjectName("treeView");
        treeView->setGeometry(QRect(710, 60, 211, 361));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 949, 25));
        menuSelecciona_el_video = new QMenu(menubar);
        menuSelecciona_el_video->setObjectName("menuSelecciona_el_video");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuSelecciona_el_video->menuAction());
        menuSelecciona_el_video->addAction(actionOpen);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Abrir", nullptr));
        groupBox_Video->setTitle(QString());
        pushButton_retroceder->setText(QString());
        label_time->setText(QCoreApplication::translate("MainWindow", "00:00:00", nullptr));
        pushButton_pausar->setText(QString());
        pushButton_adelantar->setText(QString());
        pushButton_siguiente->setText(QString());
        pushButton_anterior->setText(QString());
        pushButton_mute->setText(QString());
        pushButton_stop->setText(QString());
        menuSelecciona_el_video->setTitle(QCoreApplication::translate("MainWindow", "Selecciona el video", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
