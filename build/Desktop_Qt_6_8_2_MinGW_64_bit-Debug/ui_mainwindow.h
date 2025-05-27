/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QPushButton *submit_ajouter;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *lineEdit_ID_RDV;
    QDateEdit *dateEdit_DATE;
    QLineEdit *lineEdit_OBJET;
    QComboBox *comboBox_TYPE_RDV;
    QLabel *label_14;
    QTimeEdit *timeEdit_HEURE;
    QComboBox *comboBox_STATUT;
    QLineEdit *lineEdit_ID_RDV_Modifier;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QTimeEdit *timeEdit_HEURE_Modifier;
    QLabel *label_10;
    QDateEdit *dateEdit_DATE_Modifier;
    QComboBox *comboBox_STATUT_Modifier;
    QLabel *label_11;
    QLineEdit *lineEdit_OBJET_Modifier;
    QComboBox *comboBox_TYPE_RDV_Modifier;
    QLabel *label_12;
    QPushButton *pushButton_Modifier;
    QFrame *frame_2;
    QPushButton *pushButton_Stats;
    QComboBox *comboBox_Tri;
    QTableView *tableWidget_RDV;
    QPushButton *pushButton_Supprimer;
    QLineEdit *lineEdit_ID_RDV_Supprimer;
    QLineEdit *lineEdit_Recherche;
    QComboBox *comboBox_RechercheCritere;
    QPushButton *pushButton_Recherche;
    QPushButton *pushButton_PDF;
    QPushButton *pushButton_Calendrier;
    QLabel *label_StatsResult;
    QChartView *statsChartView;
    QMenuBar *menubar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1469, 741);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("background-color: #4a6fa5;\n"
"\n"
""));
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(50, 30, 471, 621));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius: 20px;\n"
""));
        frame->setFrameShape(QFrame::Shape::NoFrame);
        submit_ajouter = new QPushButton(frame);
        submit_ajouter->setObjectName("submit_ajouter");
        submit_ajouter->setGeometry(QRect(140, 300, 131, 29));
        submit_ajouter->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(0, 255, 127);\n"
"    border-radius: 10px;\n"
"    border: 2px solid transparent;\n"
"	color: rgb(255, 255, 255);\n"
"	font: 500 12pt \"Source Code Pro Medium\";\n"
"}\n"
""));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 58, 91, 22));
        label->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 100, 38, 22));
        label_2->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 140, 60, 22));
        label_3->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 180, 61, 21));
        label_4->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 220, 61, 21));
        label_5->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 260, 41, 21));
        label_6->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));
        lineEdit_ID_RDV = new QLineEdit(frame);
        lineEdit_ID_RDV->setObjectName("lineEdit_ID_RDV");
        lineEdit_ID_RDV->setGeometry(QRect(170, 58, 133, 32));
        lineEdit_ID_RDV->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));
        dateEdit_DATE = new QDateEdit(frame);
        dateEdit_DATE->setObjectName("dateEdit_DATE");
        dateEdit_DATE->setGeometry(QRect(170, 100, 131, 31));
        dateEdit_DATE->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));
        lineEdit_OBJET = new QLineEdit(frame);
        lineEdit_OBJET->setObjectName("lineEdit_OBJET");
        lineEdit_OBJET->setGeometry(QRect(170, 180, 133, 32));
        lineEdit_OBJET->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));
        comboBox_TYPE_RDV = new QComboBox(frame);
        comboBox_TYPE_RDV->addItem(QString());
        comboBox_TYPE_RDV->addItem(QString());
        comboBox_TYPE_RDV->setObjectName("comboBox_TYPE_RDV");
        comboBox_TYPE_RDV->setGeometry(QRect(170, 260, 133, 32));
        comboBox_TYPE_RDV->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));
        label_14 = new QLabel(frame);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(20, 10, 161, 22));
        label_14->setStyleSheet(QString::fromUtf8("font: 600 15pt \"Segoe UI\";"));
        timeEdit_HEURE = new QTimeEdit(frame);
        timeEdit_HEURE->setObjectName("timeEdit_HEURE");
        timeEdit_HEURE->setGeometry(QRect(170, 140, 131, 31));
        timeEdit_HEURE->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));
        comboBox_STATUT = new QComboBox(frame);
        comboBox_STATUT->addItem(QString());
        comboBox_STATUT->addItem(QString());
        comboBox_STATUT->addItem(QString());
        comboBox_STATUT->addItem(QString());
        comboBox_STATUT->setObjectName("comboBox_STATUT");
        comboBox_STATUT->setGeometry(QRect(169, 220, 131, 31));
        comboBox_STATUT->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));
        lineEdit_ID_RDV_Modifier = new QLineEdit(frame);
        lineEdit_ID_RDV_Modifier->setObjectName("lineEdit_ID_RDV_Modifier");
        lineEdit_ID_RDV_Modifier->setGeometry(QRect(170, 339, 133, 32));
        lineEdit_ID_RDV_Modifier->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));
        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(30, 540, 41, 21));
        label_7->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));
        label_8 = new QLabel(frame);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(30, 460, 61, 21));
        label_8->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));
        label_9 = new QLabel(frame);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(30, 420, 60, 22));
        label_9->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));
        timeEdit_HEURE_Modifier = new QTimeEdit(frame);
        timeEdit_HEURE_Modifier->setObjectName("timeEdit_HEURE_Modifier");
        timeEdit_HEURE_Modifier->setGeometry(QRect(170, 420, 131, 31));
        timeEdit_HEURE_Modifier->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));
        label_10 = new QLabel(frame);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(30, 500, 61, 21));
        label_10->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));
        dateEdit_DATE_Modifier = new QDateEdit(frame);
        dateEdit_DATE_Modifier->setObjectName("dateEdit_DATE_Modifier");
        dateEdit_DATE_Modifier->setGeometry(QRect(170, 380, 131, 31));
        dateEdit_DATE_Modifier->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));
        comboBox_STATUT_Modifier = new QComboBox(frame);
        comboBox_STATUT_Modifier->addItem(QString());
        comboBox_STATUT_Modifier->addItem(QString());
        comboBox_STATUT_Modifier->addItem(QString());
        comboBox_STATUT_Modifier->addItem(QString());
        comboBox_STATUT_Modifier->setObjectName("comboBox_STATUT_Modifier");
        comboBox_STATUT_Modifier->setGeometry(QRect(170, 500, 131, 31));
        comboBox_STATUT_Modifier->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));
        label_11 = new QLabel(frame);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(30, 339, 91, 22));
        label_11->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));
        lineEdit_OBJET_Modifier = new QLineEdit(frame);
        lineEdit_OBJET_Modifier->setObjectName("lineEdit_OBJET_Modifier");
        lineEdit_OBJET_Modifier->setGeometry(QRect(170, 460, 133, 32));
        lineEdit_OBJET_Modifier->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));
        comboBox_TYPE_RDV_Modifier = new QComboBox(frame);
        comboBox_TYPE_RDV_Modifier->addItem(QString());
        comboBox_TYPE_RDV_Modifier->addItem(QString());
        comboBox_TYPE_RDV_Modifier->setObjectName("comboBox_TYPE_RDV_Modifier");
        comboBox_TYPE_RDV_Modifier->setGeometry(QRect(170, 540, 133, 32));
        comboBox_TYPE_RDV_Modifier->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));
        label_12 = new QLabel(frame);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(30, 380, 38, 22));
        label_12->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));
        pushButton_Modifier = new QPushButton(frame);
        pushButton_Modifier->setObjectName("pushButton_Modifier");
        pushButton_Modifier->setGeometry(QRect(140, 580, 141, 31));
        pushButton_Modifier->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    \n"
"	background-color: rgb(255, 195, 16);\n"
"    border-radius: 10px;\n"
"    border: 2px solid transparent;\n"
"	color: rgb(255, 255, 255);\n"
"	font: 500 12pt \"Source Code Pro Medium\";\n"
"}\n"
""));
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(530, 30, 811, 621));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius: 20px;\n"
""));
        frame_2->setFrameShape(QFrame::Shape::NoFrame);
        pushButton_Stats = new QPushButton(frame_2);
        pushButton_Stats->setObjectName("pushButton_Stats");
        pushButton_Stats->setGeometry(QRect(630, 50, 171, 41));
        pushButton_Stats->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(142, 68, 173); /* #8E44AD */\n"
"    border-radius: 10px;\n"
"    border: 2px solid transparent;\n"
"    color: rgb(255, 255, 255);\n"
"    font: 500 12pt \"Source Code Pro Medium\";\n"
"}\n"
""));
        comboBox_Tri = new QComboBox(frame_2);
        comboBox_Tri->addItem(QString());
        comboBox_Tri->addItem(QString());
        comboBox_Tri->addItem(QString());
        comboBox_Tri->addItem(QString());
        comboBox_Tri->addItem(QString());
        comboBox_Tri->addItem(QString());
        comboBox_Tri->addItem(QString());
        comboBox_Tri->setObjectName("comboBox_Tri");
        comboBox_Tri->setGeometry(QRect(20, 20, 171, 31));
        comboBox_Tri->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));
        tableWidget_RDV = new QTableView(frame_2);
        tableWidget_RDV->setObjectName("tableWidget_RDV");
        tableWidget_RDV->setGeometry(QRect(20, 110, 761, 451));
        tableWidget_RDV->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 0.5px solid gray; /* Black border */\n"
"    border-radius: 2px; /* Rounded corners */\n"
"    selection-background-color: #8E44AD; /* Example selection color */\n"
"    selection-color: white;\n"
""));
        pushButton_Supprimer = new QPushButton(frame_2);
        pushButton_Supprimer->setObjectName("pushButton_Supprimer");
        pushButton_Supprimer->setGeometry(QRect(50, 580, 148, 29));
        pushButton_Supprimer->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    \n"
"	background-color: rgb(255, 195, 176);\n"
"    border-radius: 10px;\n"
"    border: 2px solid transparent;\n"
"	color: rgb(0, 0, 0);\n"
"	font: 500 12pt \"Source Code Pro Medium\";\n"
"}\n"
""));
        lineEdit_ID_RDV_Supprimer = new QLineEdit(frame_2);
        lineEdit_ID_RDV_Supprimer->setObjectName("lineEdit_ID_RDV_Supprimer");
        lineEdit_ID_RDV_Supprimer->setGeometry(QRect(220, 580, 133, 32));
        lineEdit_ID_RDV_Supprimer->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));
        lineEdit_Recherche = new QLineEdit(frame_2);
        lineEdit_Recherche->setObjectName("lineEdit_Recherche");
        lineEdit_Recherche->setGeometry(QRect(20, 60, 171, 31));
        lineEdit_Recherche->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */"));
        comboBox_RechercheCritere = new QComboBox(frame_2);
        comboBox_RechercheCritere->addItem(QString());
        comboBox_RechercheCritere->addItem(QString());
        comboBox_RechercheCritere->addItem(QString());
        comboBox_RechercheCritere->addItem(QString());
        comboBox_RechercheCritere->addItem(QString());
        comboBox_RechercheCritere->setObjectName("comboBox_RechercheCritere");
        comboBox_RechercheCritere->setGeometry(QRect(200, 60, 131, 31));
        comboBox_RechercheCritere->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */"));
        pushButton_Recherche = new QPushButton(frame_2);
        pushButton_Recherche->setObjectName("pushButton_Recherche");
        pushButton_Recherche->setGeometry(QRect(340, 50, 131, 41));
        pushButton_Recherche->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(52, 152, 219); /* Blue */\n"
"    border-radius: 10px;\n"
"    border: 2px solid transparent;\n"
"    color: rgb(255, 255, 255);\n"
"    font: 500 10pt \"Source Code Pro Medium\";\n"
"}"));
        pushButton_PDF = new QPushButton(frame_2);
        pushButton_PDF->setObjectName("pushButton_PDF");
        pushButton_PDF->setGeometry(QRect(470, 50, 161, 41));
        pushButton_PDF->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(231, 76, 60); /* Red */\n"
"    border-radius: 10px;\n"
"    border: 2px solid transparent;\n"
"    color: rgb(255, 255, 255);\n"
"    font: 500 10pt \"Source Code Pro Medium\";\n"
"}"));
        pushButton_Calendrier = new QPushButton(frame_2);
        pushButton_Calendrier->setObjectName("pushButton_Calendrier");
        pushButton_Calendrier->setGeometry(QRect(200, 10, 171, 41));
        pushButton_Calendrier->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #1ABC9C; /* Turquoise */\n"
"    border-radius: 10px;\n"
"    border: 2px solid transparent;\n"
"    color: rgb(255, 255, 255);\n"
"    font: 500 10pt \"Source Code Pro Medium\";\n"
"}"));
        label_StatsResult = new QLabel(frame_2);
        label_StatsResult->setObjectName("label_StatsResult");
        label_StatsResult->setGeometry(QRect(400, 570, 381, 41));
        label_StatsResult->setVisible(false);
        label_StatsResult->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";\n"
"background-color: transparent;\n"
"border: none;"));
        label_StatsResult->setWordWrap(true);
        statsChartView = new QChartView(frame_2);
        statsChartView->setObjectName("statsChartView");
        statsChartView->setGeometry(QRect(400, 570, 381, 150));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1469, 26));
        MainWindow->setMenuBar(menubar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        submit_ajouter->setText(QCoreApplication::translate("MainWindow", "CONFIRM", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "ID EVENT", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "HEURE", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "OBJET", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "STATUT", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "TYPE", nullptr));
        comboBox_TYPE_RDV->setItemText(0, QCoreApplication::translate("MainWindow", "onsite", nullptr));
        comboBox_TYPE_RDV->setItemText(1, QCoreApplication::translate("MainWindow", "online", nullptr));

        label_14->setText(QCoreApplication::translate("MainWindow", "Entr\303\251e", nullptr));
        comboBox_STATUT->setItemText(0, QCoreApplication::translate("MainWindow", "Pending", nullptr));
        comboBox_STATUT->setItemText(1, QCoreApplication::translate("MainWindow", "Confirmed", nullptr));
        comboBox_STATUT->setItemText(2, QCoreApplication::translate("MainWindow", "cancelled", nullptr));
        comboBox_STATUT->setItemText(3, QCoreApplication::translate("MainWindow", "done", nullptr));

        label_7->setText(QCoreApplication::translate("MainWindow", "TYPE", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "OBJET", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "HEURE", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "STATUT", nullptr));
        comboBox_STATUT_Modifier->setItemText(0, QCoreApplication::translate("MainWindow", "pending", nullptr));
        comboBox_STATUT_Modifier->setItemText(1, QCoreApplication::translate("MainWindow", "Confirmed", nullptr));
        comboBox_STATUT_Modifier->setItemText(2, QCoreApplication::translate("MainWindow", "cancelled", nullptr));
        comboBox_STATUT_Modifier->setItemText(3, QCoreApplication::translate("MainWindow", "done", nullptr));

        label_11->setText(QCoreApplication::translate("MainWindow", "ID EVENT", nullptr));
        comboBox_TYPE_RDV_Modifier->setItemText(0, QCoreApplication::translate("MainWindow", "onsite", nullptr));
        comboBox_TYPE_RDV_Modifier->setItemText(1, QCoreApplication::translate("MainWindow", "online", nullptr));

        label_12->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        pushButton_Modifier->setText(QCoreApplication::translate("MainWindow", "MODIFY", nullptr));
        pushButton_Stats->setText(QCoreApplication::translate("MainWindow", "Show Stats", nullptr));
        comboBox_Tri->setItemText(0, QCoreApplication::translate("MainWindow", "Sort by...", nullptr));
        comboBox_Tri->setItemText(1, QCoreApplication::translate("MainWindow", "ID_RDV", nullptr));
        comboBox_Tri->setItemText(2, QCoreApplication::translate("MainWindow", "Date", nullptr));
        comboBox_Tri->setItemText(3, QCoreApplication::translate("MainWindow", "Heure", nullptr));
        comboBox_Tri->setItemText(4, QCoreApplication::translate("MainWindow", "Objet", nullptr));
        comboBox_Tri->setItemText(5, QCoreApplication::translate("MainWindow", "Statut", nullptr));
        comboBox_Tri->setItemText(6, QCoreApplication::translate("MainWindow", "TYPE", nullptr));

        pushButton_Supprimer->setText(QCoreApplication::translate("MainWindow", "DELETE", nullptr));
        lineEdit_Recherche->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher...", nullptr));
        comboBox_RechercheCritere->setItemText(0, QCoreApplication::translate("MainWindow", "Criteria..", nullptr));
        comboBox_RechercheCritere->setItemText(1, QCoreApplication::translate("MainWindow", "ID_RDV", nullptr));
        comboBox_RechercheCritere->setItemText(2, QCoreApplication::translate("MainWindow", "Objet", nullptr));
        comboBox_RechercheCritere->setItemText(3, QCoreApplication::translate("MainWindow", "Statut", nullptr));
        comboBox_RechercheCritere->setItemText(4, QCoreApplication::translate("MainWindow", "TYPE", nullptr));

        pushButton_Recherche->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        pushButton_PDF->setText(QCoreApplication::translate("MainWindow", "Generate PDF", nullptr));
        pushButton_Calendrier->setText(QCoreApplication::translate("MainWindow", "Open Calendar", nullptr));
        label_StatsResult->setText(QCoreApplication::translate("MainWindow", "Statistiques par Objet: (Cliquez sur le bouton)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
