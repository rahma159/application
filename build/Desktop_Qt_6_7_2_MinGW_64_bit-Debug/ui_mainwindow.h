/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
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
    QPushButton *pushButton_2;
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
    QLabel *label_15;
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
    QStatusBar *statusbar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1353, 759);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:0, \n"
"stop:0 #ddb5ed, \n"
"stop:0.25 #9B59B6, \n"
"stop:0.5 #8E44AD, \n"
"stop:0.75 #9B59B6, \n"
"stop:1 #ddb5ed);\n"
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
        submit_ajouter->setGeometry(QRect(40, 290, 112, 29));
        submit_ajouter->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(0, 255, 127);\n"
"    border-radius: 10px;\n"
"    border: 2px solid transparent;\n"
"	color: rgb(255, 255, 255);\n"
"	font: 500 12pt \"Source Code Pro Medium\";\n"
"}\n"
""));
        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(190, 290, 148, 29));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    \n"
"	background-color: rgb(255, 195, 16);\n"
"    border-radius: 10px;\n"
"    border: 2px solid transparent;\n"
"	color: rgb(255, 255, 255);\n"
"	font: 500 12pt \"Source Code Pro Medium\";\n"
"}\n"
""));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 58, 61, 22));
        label->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 99, 38, 22));
        label_2->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 130, 60, 22));
        label_3->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 171, 61, 21));
        label_4->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 212, 61, 21));
        label_5->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 253, 41, 21));
        label_6->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));
        lineEdit_ID_RDV = new QLineEdit(frame);
        lineEdit_ID_RDV->setObjectName("lineEdit_ID_RDV");
        lineEdit_ID_RDV->setGeometry(QRect(175, 58, 133, 32));
        lineEdit_ID_RDV->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));
        dateEdit_DATE = new QDateEdit(frame);
        dateEdit_DATE->setObjectName("dateEdit_DATE");
        dateEdit_DATE->setGeometry(QRect(175, 99, 131, 22));
        dateEdit_DATE->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));
        lineEdit_OBJET = new QLineEdit(frame);
        lineEdit_OBJET->setObjectName("lineEdit_OBJET");
        lineEdit_OBJET->setGeometry(QRect(175, 171, 133, 32));
        lineEdit_OBJET->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));
        comboBox_TYPE_RDV = new QComboBox(frame);
        comboBox_TYPE_RDV->addItem(QString());
        comboBox_TYPE_RDV->addItem(QString());
        comboBox_TYPE_RDV->addItem(QString());
        comboBox_TYPE_RDV->setObjectName("comboBox_TYPE_RDV");
        comboBox_TYPE_RDV->setGeometry(QRect(175, 253, 133, 32));
        label_14 = new QLabel(frame);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(20, 10, 161, 22));
        label_14->setStyleSheet(QString::fromUtf8("font: 600 15pt \"Segoe UI\";"));
        timeEdit_HEURE = new QTimeEdit(frame);
        timeEdit_HEURE->setObjectName("timeEdit_HEURE");
        timeEdit_HEURE->setGeometry(QRect(180, 130, 118, 26));
        comboBox_STATUT = new QComboBox(frame);
        comboBox_STATUT->addItem(QString());
        comboBox_STATUT->addItem(QString());
        comboBox_STATUT->addItem(QString());
        comboBox_STATUT->addItem(QString());
        comboBox_STATUT->setObjectName("comboBox_STATUT");
        comboBox_STATUT->setGeometry(QRect(200, 220, 80, 26));
        lineEdit_ID_RDV_Modifier = new QLineEdit(frame);
        lineEdit_ID_RDV_Modifier->setObjectName("lineEdit_ID_RDV_Modifier");
        lineEdit_ID_RDV_Modifier->setGeometry(QRect(185, 339, 133, 32));
        lineEdit_ID_RDV_Modifier->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));
        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(30, 534, 41, 21));
        label_7->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));
        label_8 = new QLabel(frame);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(30, 452, 61, 21));
        label_8->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));
        label_9 = new QLabel(frame);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(30, 411, 60, 22));
        label_9->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));
        timeEdit_HEURE_Modifier = new QTimeEdit(frame);
        timeEdit_HEURE_Modifier->setObjectName("timeEdit_HEURE_Modifier");
        timeEdit_HEURE_Modifier->setGeometry(QRect(190, 411, 118, 26));
        label_10 = new QLabel(frame);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(30, 493, 61, 21));
        label_10->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));
        dateEdit_DATE_Modifier = new QDateEdit(frame);
        dateEdit_DATE_Modifier->setObjectName("dateEdit_DATE_Modifier");
        dateEdit_DATE_Modifier->setGeometry(QRect(185, 380, 131, 22));
        dateEdit_DATE_Modifier->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));
        comboBox_STATUT_Modifier = new QComboBox(frame);
        comboBox_STATUT_Modifier->addItem(QString());
        comboBox_STATUT_Modifier->addItem(QString());
        comboBox_STATUT_Modifier->setObjectName("comboBox_STATUT_Modifier");
        comboBox_STATUT_Modifier->setGeometry(QRect(210, 501, 80, 26));
        label_11 = new QLabel(frame);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(30, 339, 61, 22));
        label_11->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));
        lineEdit_OBJET_Modifier = new QLineEdit(frame);
        lineEdit_OBJET_Modifier->setObjectName("lineEdit_OBJET_Modifier");
        lineEdit_OBJET_Modifier->setGeometry(QRect(185, 452, 133, 32));
        lineEdit_OBJET_Modifier->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));
        comboBox_TYPE_RDV_Modifier = new QComboBox(frame);
        comboBox_TYPE_RDV_Modifier->addItem(QString());
        comboBox_TYPE_RDV_Modifier->addItem(QString());
        comboBox_TYPE_RDV_Modifier->addItem(QString());
        comboBox_TYPE_RDV_Modifier->setObjectName("comboBox_TYPE_RDV_Modifier");
        comboBox_TYPE_RDV_Modifier->setGeometry(QRect(185, 534, 133, 32));
        label_12 = new QLabel(frame);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(30, 380, 38, 22));
        label_12->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));
        pushButton_Modifier = new QPushButton(frame);
        pushButton_Modifier->setObjectName("pushButton_Modifier");
        pushButton_Modifier->setGeometry(QRect(110, 580, 148, 29));
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
        label_15 = new QLabel(frame_2);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(10, 0, 191, 51));
        label_15->setStyleSheet(QString::fromUtf8("font: 600 15pt \"Segoe UI\";"));
        pushButton_Stats = new QPushButton(frame_2);
        pushButton_Stats->setObjectName("pushButton_Stats");
        pushButton_Stats->setGeometry(QRect(590, 60, 181, 31));
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
"	background-color: rgb(255, 195, 16);\n"
"    border-radius: 10px;\n"
"    border: 2px solid transparent;\n"
"	color: rgb(255, 255, 255);\n"
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
        pushButton_Recherche->setGeometry(QRect(340, 60, 101, 31));
        pushButton_Recherche->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(52, 152, 219); /* Blue */\n"
"    border-radius: 10px;\n"
"    border: 2px solid transparent;\n"
"    color: rgb(255, 255, 255);\n"
"    font: 500 10pt \"Source Code Pro Medium\";\n"
"}"));
        pushButton_PDF = new QPushButton(frame_2);
        pushButton_PDF->setObjectName("pushButton_PDF");
        pushButton_PDF->setGeometry(QRect(450, 60, 131, 31));
        pushButton_PDF->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(231, 76, 60); /* Red */\n"
"    border-radius: 10px;\n"
"    border: 2px solid transparent;\n"
"    color: rgb(255, 255, 255);\n"
"    font: 500 10pt \"Source Code Pro Medium\";\n"
"}"));
        pushButton_Calendrier = new QPushButton(frame_2);
        pushButton_Calendrier->setObjectName("pushButton_Calendrier");
        pushButton_Calendrier->setGeometry(QRect(200, 20, 171, 31));
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
        label_StatsResult->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        label_StatsResult->setWordWrap(true);
        statsChartView = new QChartView(frame_2);
        statsChartView->setObjectName("statsChartView");
        statsChartView->setGeometry(QRect(400, 570, 381, 150));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1353, 26));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        submit_ajouter->setText(QCoreApplication::translate("MainWindow", "Confirmer", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "R\303\251instaliser", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "ID RDV", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "HEURE", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "OBJET", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "STATUT", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "TYPE", nullptr));
        comboBox_TYPE_RDV->setItemText(0, QCoreApplication::translate("MainWindow", "onsite", nullptr));
        comboBox_TYPE_RDV->setItemText(1, QCoreApplication::translate("MainWindow", "online", nullptr));
        comboBox_TYPE_RDV->setItemText(2, QCoreApplication::translate("MainWindow", "hybrid", nullptr));

        label_14->setText(QCoreApplication::translate("MainWindow", "Entr\303\251e", nullptr));
        comboBox_STATUT->setItemText(0, QCoreApplication::translate("MainWindow", "En attente", nullptr));
        comboBox_STATUT->setItemText(1, QCoreApplication::translate("MainWindow", "Confirm\303\251", nullptr));
        comboBox_STATUT->setItemText(2, QCoreApplication::translate("MainWindow", "Annul\303\251", nullptr));
        comboBox_STATUT->setItemText(3, QCoreApplication::translate("MainWindow", "Termin\303\251", nullptr));

        label_7->setText(QCoreApplication::translate("MainWindow", "TYPE", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "OBJET", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "HEURE", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "STATUT", nullptr));
        comboBox_STATUT_Modifier->setItemText(0, QCoreApplication::translate("MainWindow", "a", nullptr));
        comboBox_STATUT_Modifier->setItemText(1, QCoreApplication::translate("MainWindow", "b", nullptr));

        label_11->setText(QCoreApplication::translate("MainWindow", "ID RDV", nullptr));
        comboBox_TYPE_RDV_Modifier->setItemText(0, QCoreApplication::translate("MainWindow", "onsite", nullptr));
        comboBox_TYPE_RDV_Modifier->setItemText(1, QCoreApplication::translate("MainWindow", "online", nullptr));
        comboBox_TYPE_RDV_Modifier->setItemText(2, QCoreApplication::translate("MainWindow", "hybrid", nullptr));

        label_12->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        pushButton_Modifier->setText(QCoreApplication::translate("MainWindow", "MODIFIER", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Affichage", nullptr));
        pushButton_Stats->setText(QCoreApplication::translate("MainWindow", "Afficher Stats Objet", nullptr));
        comboBox_Tri->setItemText(0, QCoreApplication::translate("MainWindow", "Trier par...", nullptr));
        comboBox_Tri->setItemText(1, QCoreApplication::translate("MainWindow", "ID_RDV", nullptr));
        comboBox_Tri->setItemText(2, QCoreApplication::translate("MainWindow", "DATERDV", nullptr));
        comboBox_Tri->setItemText(3, QCoreApplication::translate("MainWindow", "HEURE", nullptr));
        comboBox_Tri->setItemText(4, QCoreApplication::translate("MainWindow", "OBJET", nullptr));
        comboBox_Tri->setItemText(5, QCoreApplication::translate("MainWindow", "STATUT", nullptr));
        comboBox_Tri->setItemText(6, QCoreApplication::translate("MainWindow", "TYPE", nullptr));

        pushButton_Supprimer->setText(QCoreApplication::translate("MainWindow", "SUPPRIMER", nullptr));
        lineEdit_Recherche->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher...", nullptr));
        comboBox_RechercheCritere->setItemText(0, QCoreApplication::translate("MainWindow", "Crit\303\250re...", nullptr));
        comboBox_RechercheCritere->setItemText(1, QCoreApplication::translate("MainWindow", "ID_RDV", nullptr));
        comboBox_RechercheCritere->setItemText(2, QCoreApplication::translate("MainWindow", "OBJET", nullptr));
        comboBox_RechercheCritere->setItemText(3, QCoreApplication::translate("MainWindow", "STATUT", nullptr));
        comboBox_RechercheCritere->setItemText(4, QCoreApplication::translate("MainWindow", "TYPE", nullptr));

        pushButton_Recherche->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        pushButton_PDF->setText(QCoreApplication::translate("MainWindow", "G\303\251n\303\251rer PDF", nullptr));
        pushButton_Calendrier->setText(QCoreApplication::translate("MainWindow", "Ouvrir Calendrier", nullptr));
        label_StatsResult->setText(QCoreApplication::translate("MainWindow", "Statistiques par Objet: (Cliquez sur le bouton)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
