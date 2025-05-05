QT       += core gui widgets sql charts  # charts for QChartView, sql for database

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = consulting_office
TEMPLATE = app

SOURCES += \
    main.cpp \
    enhanced_mainwindow.cpp \
    enhanced_addeditdialog.cpp \
    imagepreviewdialog.cpp

HEADERS += \
    enhanced_mainwindow.h \
    enhanced_addeditdialog.h \
    imagepreviewdialog.h

FORMS += \
    enhanced_mainwindow.ui \
    enhanced_addeditdialog.ui

RESOURCES += \
    resources.qrc
