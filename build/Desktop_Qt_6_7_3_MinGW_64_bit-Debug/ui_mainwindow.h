/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QComboBox *comboBox_TYPE_RDV_Modifier;
    QLabel *label;
    QLabel *label_9;
    QLabel *label_4;
    QDateEdit *dateEdit_DATE;
    QLineEdit *lineEdit_ID_RDV_Modifier;
    QLabel *label_10;
    QLabel *label_7;
    QTimeEdit *timeEdit_HEURE;
    QComboBox *comboBox_STATUT;
    QTimeEdit *timeEdit_HEURE_Modifier;
    QLineEdit *lineEdit_OBJET_Modifier;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Modifier;
    QLabel *label_8;
    QLabel *label_12;
    QLineEdit *lineEdit_OBJET;
    QLabel *label_11;
    QLabel *label_6;
    QComboBox *comboBox_STATUT_Modifier;
    QSpacerItem *verticalSpacer_2;
    QComboBox *comboBox_TYPE_RDV;
    QDateEdit *dateEdit_DATE_Modifier;
    QLabel *label_14;
    QLineEdit *lineEdit_ID_RDV;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *submit_ajouter;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer;
    QFrame *frame_2;
    QLabel *label_StatsResult;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_Calendrier;
    QSpacerItem *verticalSpacer_4;
    QLineEdit *lineEdit_ID_RDV_Supprimer;
    QLineEdit *lineEdit_Recherche;
    QPushButton *pushButton_Supprimer;
    QComboBox *comboBox_RechercheCritere;
    QTableView *tableWidget_RDV;
    QComboBox *comboBox_Tri;
    QPushButton *pushButton_Recherche;
    QPushButton *pushButton_Stats;
    QPushButton *pushButton_PDF;
    QChartView *statsChartView;
    QSpacerItem *horizontalSpacer_4;
    QMenuBar *menubar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1078, 621);
        MainWindow->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 71);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("background-color: #4a6fa5;\n"
"\n"
""));
        horizontalLayout_3 = new QHBoxLayout(centralwidget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius: 20px;\n"
""));
        frame->setFrameShape(QFrame::Shape::NoFrame);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName("gridLayout");
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        comboBox_TYPE_RDV_Modifier = new QComboBox(frame);
        comboBox_TYPE_RDV_Modifier->addItem(QString());
        comboBox_TYPE_RDV_Modifier->addItem(QString());
        comboBox_TYPE_RDV_Modifier->setObjectName("comboBox_TYPE_RDV_Modifier");
        comboBox_TYPE_RDV_Modifier->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));

        gridLayout->addWidget(comboBox_TYPE_RDV_Modifier, 14, 2, 1, 1);

        label = new QLabel(frame);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));

        gridLayout->addWidget(label, 2, 0, 1, 2);

        label_9 = new QLabel(frame);
        label_9->setObjectName("label_9");
        label_9->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));

        gridLayout->addWidget(label_9, 11, 0, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));

        gridLayout->addWidget(label_4, 5, 0, 1, 1);

        dateEdit_DATE = new QDateEdit(frame);
        dateEdit_DATE->setObjectName("dateEdit_DATE");
        dateEdit_DATE->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));

        gridLayout->addWidget(dateEdit_DATE, 3, 2, 1, 1);

        lineEdit_ID_RDV_Modifier = new QLineEdit(frame);
        lineEdit_ID_RDV_Modifier->setObjectName("lineEdit_ID_RDV_Modifier");
        lineEdit_ID_RDV_Modifier->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));

        gridLayout->addWidget(lineEdit_ID_RDV_Modifier, 9, 2, 1, 1);

        label_10 = new QLabel(frame);
        label_10->setObjectName("label_10");
        label_10->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));

        gridLayout->addWidget(label_10, 13, 0, 1, 1);

        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));

        gridLayout->addWidget(label_7, 14, 0, 1, 1);

        timeEdit_HEURE = new QTimeEdit(frame);
        timeEdit_HEURE->setObjectName("timeEdit_HEURE");
        timeEdit_HEURE->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));

        gridLayout->addWidget(timeEdit_HEURE, 4, 2, 1, 1);

        comboBox_STATUT = new QComboBox(frame);
        comboBox_STATUT->addItem(QString());
        comboBox_STATUT->addItem(QString());
        comboBox_STATUT->addItem(QString());
        comboBox_STATUT->addItem(QString());
        comboBox_STATUT->setObjectName("comboBox_STATUT");
        comboBox_STATUT->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));

        gridLayout->addWidget(comboBox_STATUT, 6, 2, 1, 1);

        timeEdit_HEURE_Modifier = new QTimeEdit(frame);
        timeEdit_HEURE_Modifier->setObjectName("timeEdit_HEURE_Modifier");
        timeEdit_HEURE_Modifier->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));

        gridLayout->addWidget(timeEdit_HEURE_Modifier, 11, 2, 1, 1);

        lineEdit_OBJET_Modifier = new QLineEdit(frame);
        lineEdit_OBJET_Modifier->setObjectName("lineEdit_OBJET_Modifier");
        lineEdit_OBJET_Modifier->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));

        gridLayout->addWidget(lineEdit_OBJET_Modifier, 12, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_Modifier = new QPushButton(frame);
        pushButton_Modifier->setObjectName("pushButton_Modifier");
        pushButton_Modifier->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    \n"
"	background-color: rgb(255, 195, 16);\n"
"    border-radius: 10px;\n"
"    border: 2px solid transparent;\n"
"	color: rgb(255, 255, 255);\n"
"	font: 500 12pt \"Source Code Pro Medium\";\n"
"}\n"
""));

        horizontalLayout->addWidget(pushButton_Modifier);


        gridLayout->addLayout(horizontalLayout, 15, 2, 1, 1);

        label_8 = new QLabel(frame);
        label_8->setObjectName("label_8");
        label_8->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));

        gridLayout->addWidget(label_8, 12, 0, 1, 1);

        label_12 = new QLabel(frame);
        label_12->setObjectName("label_12");
        label_12->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));

        gridLayout->addWidget(label_12, 10, 0, 1, 1);

        lineEdit_OBJET = new QLineEdit(frame);
        lineEdit_OBJET->setObjectName("lineEdit_OBJET");
        lineEdit_OBJET->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));

        gridLayout->addWidget(lineEdit_OBJET, 5, 2, 1, 1);

        label_11 = new QLabel(frame);
        label_11->setObjectName("label_11");
        label_11->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));

        gridLayout->addWidget(label_11, 9, 0, 1, 2);

        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));

        gridLayout->addWidget(label_6, 7, 0, 1, 1);

        comboBox_STATUT_Modifier = new QComboBox(frame);
        comboBox_STATUT_Modifier->addItem(QString());
        comboBox_STATUT_Modifier->addItem(QString());
        comboBox_STATUT_Modifier->addItem(QString());
        comboBox_STATUT_Modifier->addItem(QString());
        comboBox_STATUT_Modifier->setObjectName("comboBox_STATUT_Modifier");
        comboBox_STATUT_Modifier->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));

        gridLayout->addWidget(comboBox_STATUT_Modifier, 13, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        gridLayout->addItem(verticalSpacer_2, 16, 2, 1, 1);

        comboBox_TYPE_RDV = new QComboBox(frame);
        comboBox_TYPE_RDV->addItem(QString());
        comboBox_TYPE_RDV->addItem(QString());
        comboBox_TYPE_RDV->setObjectName("comboBox_TYPE_RDV");
        comboBox_TYPE_RDV->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));

        gridLayout->addWidget(comboBox_TYPE_RDV, 7, 2, 1, 1);

        dateEdit_DATE_Modifier = new QDateEdit(frame);
        dateEdit_DATE_Modifier->setObjectName("dateEdit_DATE_Modifier");
        dateEdit_DATE_Modifier->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));

        gridLayout->addWidget(dateEdit_DATE_Modifier, 10, 2, 1, 1);

        label_14 = new QLabel(frame);
        label_14->setObjectName("label_14");
        label_14->setStyleSheet(QString::fromUtf8("font: 600 15pt \"Segoe UI\";"));

        gridLayout->addWidget(label_14, 1, 0, 1, 3);

        lineEdit_ID_RDV = new QLineEdit(frame);
        lineEdit_ID_RDV->setObjectName("lineEdit_ID_RDV");
        lineEdit_ID_RDV->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));

        gridLayout->addWidget(lineEdit_ID_RDV, 2, 2, 1, 1);

        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));

        gridLayout->addWidget(label_5, 6, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        submit_ajouter = new QPushButton(frame);
        submit_ajouter->setObjectName("submit_ajouter");
        submit_ajouter->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(0, 255, 127);\n"
"    border-radius: 10px;\n"
"    border: 2px solid transparent;\n"
"	color: rgb(255, 255, 255);\n"
"	font: 500 12pt \"Source Code Pro Medium\";\n"
"}\n"
""));

        horizontalLayout_2->addWidget(submit_ajouter);


        gridLayout->addLayout(horizontalLayout_2, 8, 1, 1, 2);

        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";"));

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        gridLayout->addItem(verticalSpacer_3, 0, 0, 1, 1);


        horizontalLayout_3->addWidget(frame);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        horizontalLayout_3->addItem(verticalSpacer);

        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName("frame_2");
        frame_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius: 20px;\n"
""));
        frame_2->setFrameShape(QFrame::Shape::NoFrame);
        label_StatsResult = new QLabel(frame_2);
        label_StatsResult->setObjectName("label_StatsResult");
        label_StatsResult->setGeometry(QRect(400, 570, 381, 41));
        label_StatsResult->setVisible(false);
        label_StatsResult->setStyleSheet(QString::fromUtf8("font: 600 10pt \"Segoe UI\";\n"
"background-color: transparent;\n"
"border: none;"));
        label_StatsResult->setWordWrap(true);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setObjectName("gridLayout_2");
        pushButton_Calendrier = new QPushButton(frame_2);
        pushButton_Calendrier->setObjectName("pushButton_Calendrier");
        pushButton_Calendrier->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #1ABC9C; /* Turquoise */\n"
"    border-radius: 10px;\n"
"    border: 2px solid transparent;\n"
"    color: rgb(255, 255, 255);\n"
"    font: 500 10pt \"Source Code Pro Medium\";\n"
"}"));

        gridLayout_2->addWidget(pushButton_Calendrier, 1, 1, 1, 2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        gridLayout_2->addItem(verticalSpacer_4, 0, 1, 1, 1);

        lineEdit_ID_RDV_Supprimer = new QLineEdit(frame_2);
        lineEdit_ID_RDV_Supprimer->setObjectName("lineEdit_ID_RDV_Supprimer");
        lineEdit_ID_RDV_Supprimer->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));

        gridLayout_2->addWidget(lineEdit_ID_RDV_Supprimer, 4, 1, 1, 2);

        lineEdit_Recherche = new QLineEdit(frame_2);
        lineEdit_Recherche->setObjectName("lineEdit_Recherche");
        lineEdit_Recherche->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */"));

        gridLayout_2->addWidget(lineEdit_Recherche, 2, 0, 1, 1);

        pushButton_Supprimer = new QPushButton(frame_2);
        pushButton_Supprimer->setObjectName("pushButton_Supprimer");
        pushButton_Supprimer->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    \n"
"	background-color: rgb(255, 195, 176);\n"
"    border-radius: 10px;\n"
"    border: 2px solid transparent;\n"
"	color: rgb(0, 0, 0);\n"
"	font: 500 12pt \"Source Code Pro Medium\";\n"
"}\n"
""));

        gridLayout_2->addWidget(pushButton_Supprimer, 4, 0, 1, 1);

        comboBox_RechercheCritere = new QComboBox(frame_2);
        comboBox_RechercheCritere->addItem(QString());
        comboBox_RechercheCritere->addItem(QString());
        comboBox_RechercheCritere->addItem(QString());
        comboBox_RechercheCritere->addItem(QString());
        comboBox_RechercheCritere->addItem(QString());
        comboBox_RechercheCritere->setObjectName("comboBox_RechercheCritere");
        comboBox_RechercheCritere->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */"));

        gridLayout_2->addWidget(comboBox_RechercheCritere, 2, 1, 1, 1);

        tableWidget_RDV = new QTableView(frame_2);
        tableWidget_RDV->setObjectName("tableWidget_RDV");
        tableWidget_RDV->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 0.5px solid gray; /* Black border */\n"
"    border-radius: 2px; /* Rounded corners */\n"
"    selection-background-color: #8E44AD; /* Example selection color */\n"
"    selection-color: white;\n"
""));

        gridLayout_2->addWidget(tableWidget_RDV, 3, 0, 1, 6);

        comboBox_Tri = new QComboBox(frame_2);
        comboBox_Tri->addItem(QString());
        comboBox_Tri->addItem(QString());
        comboBox_Tri->addItem(QString());
        comboBox_Tri->addItem(QString());
        comboBox_Tri->addItem(QString());
        comboBox_Tri->addItem(QString());
        comboBox_Tri->addItem(QString());
        comboBox_Tri->setObjectName("comboBox_Tri");
        comboBox_Tri->setStyleSheet(QString::fromUtf8("    background-color: rgb(249, 249, 249); /* Slightly grayish white */\n"
"    border: 1px solid black; /* Black border */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 4px; /* Adds spacing inside for better look */\n"
"\n"
""));

        gridLayout_2->addWidget(comboBox_Tri, 1, 0, 1, 1);

        pushButton_Recherche = new QPushButton(frame_2);
        pushButton_Recherche->setObjectName("pushButton_Recherche");
        pushButton_Recherche->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(52, 152, 219); /* Blue */\n"
"    border-radius: 10px;\n"
"    border: 2px solid transparent;\n"
"    color: rgb(255, 255, 255);\n"
"    font: 500 10pt \"Source Code Pro Medium\";\n"
"}"));

        gridLayout_2->addWidget(pushButton_Recherche, 2, 2, 1, 2);

        pushButton_Stats = new QPushButton(frame_2);
        pushButton_Stats->setObjectName("pushButton_Stats");
        pushButton_Stats->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(pushButton_Stats, 2, 5, 1, 1);

        pushButton_PDF = new QPushButton(frame_2);
        pushButton_PDF->setObjectName("pushButton_PDF");
        pushButton_PDF->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(231, 76, 60); /* Red */\n"
"    border-radius: 10px;\n"
"    border: 2px solid transparent;\n"
"    color: rgb(255, 255, 255);\n"
"    font: 500 10pt \"Source Code Pro Medium\";\n"
"}"));

        gridLayout_2->addWidget(pushButton_PDF, 2, 4, 1, 1);

        statsChartView = new QChartView(frame_2);
        statsChartView->setObjectName("statsChartView");

        gridLayout_2->addWidget(statsChartView, 4, 3, 1, 3);


        horizontalLayout_3->addWidget(frame_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1078, 21));
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
        label_2->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        comboBox_TYPE_RDV_Modifier->setItemText(0, QCoreApplication::translate("MainWindow", "onsite", nullptr));
        comboBox_TYPE_RDV_Modifier->setItemText(1, QCoreApplication::translate("MainWindow", "online", nullptr));

        label->setText(QCoreApplication::translate("MainWindow", "ID EVENT", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "HEURE", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "OBJET", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "STATUT", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "TYPE", nullptr));
        comboBox_STATUT->setItemText(0, QCoreApplication::translate("MainWindow", "Pending", nullptr));
        comboBox_STATUT->setItemText(1, QCoreApplication::translate("MainWindow", "Confirmed", nullptr));
        comboBox_STATUT->setItemText(2, QCoreApplication::translate("MainWindow", "cancelled", nullptr));
        comboBox_STATUT->setItemText(3, QCoreApplication::translate("MainWindow", "done", nullptr));

        pushButton_Modifier->setText(QCoreApplication::translate("MainWindow", "MODIFY", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "OBJET", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "ID EVENT", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "TYPE", nullptr));
        comboBox_STATUT_Modifier->setItemText(0, QCoreApplication::translate("MainWindow", "pending", nullptr));
        comboBox_STATUT_Modifier->setItemText(1, QCoreApplication::translate("MainWindow", "Confirmed", nullptr));
        comboBox_STATUT_Modifier->setItemText(2, QCoreApplication::translate("MainWindow", "cancelled", nullptr));
        comboBox_STATUT_Modifier->setItemText(3, QCoreApplication::translate("MainWindow", "done", nullptr));

        comboBox_TYPE_RDV->setItemText(0, QCoreApplication::translate("MainWindow", "onsite", nullptr));
        comboBox_TYPE_RDV->setItemText(1, QCoreApplication::translate("MainWindow", "online", nullptr));

        label_14->setText(QCoreApplication::translate("MainWindow", "Entr\303\251e", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "STATUT", nullptr));
        submit_ajouter->setText(QCoreApplication::translate("MainWindow", "CONFIRM", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "HEURE", nullptr));
        label_StatsResult->setText(QCoreApplication::translate("MainWindow", "Statistiques par Objet: (Cliquez sur le bouton)", nullptr));
        pushButton_Calendrier->setText(QCoreApplication::translate("MainWindow", "Open Calendar", nullptr));
        lineEdit_Recherche->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher...", nullptr));
        pushButton_Supprimer->setText(QCoreApplication::translate("MainWindow", "DELETE", nullptr));
        comboBox_RechercheCritere->setItemText(0, QCoreApplication::translate("MainWindow", "Criteria..", nullptr));
        comboBox_RechercheCritere->setItemText(1, QCoreApplication::translate("MainWindow", "ID_RDV", nullptr));
        comboBox_RechercheCritere->setItemText(2, QCoreApplication::translate("MainWindow", "Objet", nullptr));
        comboBox_RechercheCritere->setItemText(3, QCoreApplication::translate("MainWindow", "Statut", nullptr));
        comboBox_RechercheCritere->setItemText(4, QCoreApplication::translate("MainWindow", "TYPE", nullptr));

        comboBox_Tri->setItemText(0, QCoreApplication::translate("MainWindow", "Sort by...", nullptr));
        comboBox_Tri->setItemText(1, QCoreApplication::translate("MainWindow", "ID_RDV", nullptr));
        comboBox_Tri->setItemText(2, QCoreApplication::translate("MainWindow", "Date", nullptr));
        comboBox_Tri->setItemText(3, QCoreApplication::translate("MainWindow", "Heure", nullptr));
        comboBox_Tri->setItemText(4, QCoreApplication::translate("MainWindow", "Objet", nullptr));
        comboBox_Tri->setItemText(5, QCoreApplication::translate("MainWindow", "Statut", nullptr));
        comboBox_Tri->setItemText(6, QCoreApplication::translate("MainWindow", "TYPE", nullptr));

        pushButton_Recherche->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        pushButton_Stats->setText(QCoreApplication::translate("MainWindow", "Show Stats", nullptr));
        pushButton_PDF->setText(QCoreApplication::translate("MainWindow", "Generate PDF", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
