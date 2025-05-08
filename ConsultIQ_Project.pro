
QT += core gui widgets sql printsupport network
QT += charts

TARGET = ConsultIQ_Project   # Name of your final executable
TEMPLATE = app              # Type of project (application)

CONFIG += c++17
# Source files
SOURCES += \
    main.cpp \
    loginandmenu.cpp\
    clientpaymentwidget.cpp \
    connection.cpp \
    createeditinvoicedialog.cpp \
    deleteinvoicedialog.cpp \
    invoicemanagementwidget.cpp \
    settingsdialog.cpp \
    statisticsdialog.cpp\
    enhanced_mainwindow.cpp \
    enhanced_addeditdialog.cpp \
    imagepreviewdialog.cpp\
    clientmanager.cpp \
    chartdialog.cpp \
    gestionreclam.cpp \
    ajoutreclamationdialog.cpp\
    client.cpp \
    history.cpp \
    mainwindow.cpp \
    modclient.cpp \
    newclient.cpp

# Header files
HEADERS += \
    loginandmenu.h\
    clientpaymentwidget.h \
    connection.h \
    createeditinvoicedialog.h \
    deleteinvoicedialog.h \
    invoicemanagementwidget.h \
    settingsdialog.h \
    statisticsdialog.h\
    enhanced_mainwindow.h \
    enhanced_addeditdialog.h \
    imagepreviewdialog.h\
    clientmanager.h \
    chartdialog.h \
    gestionreclam.h \
    ajoutreclamationdialog.h\
    client.h \
    history.h \
    mainwindow.h \
    modclient.h \
    newclient.h

# UI form files
FORMS += \
    clientmanager.ui \
    loginandmenu.ui\
    clientpaymentwidget.ui \
    createeditinvoicedialog.ui \
    deleteinvoicedialog.ui \
    invoicemanagementwidget.ui \
    settingsdialog.ui \
    statisticsdialog.ui\
    enhanced_mainwindow.ui \
    enhanced_addeditdialog.ui\
    ajoutreclamationdialog.ui \
    chartdialog.ui \
    gestionreclam.ui\
    history.ui \
    mainwindow.ui \
    modclient.ui \
    newclient.ui

DISTFILES += \
    client_payment_style.qss \
    client_payment_style.qss \
    client_payment_style.qss \
    settings_style.qss \
    settings_style.qss \
    settings_style.qss \
    style.qss \
    style_payment \
    style_payment.qss
    style_payment.qss
# Resource file
TRANSLATIONS +=
CONFIG += lrelease
CONFIG += embed_translations
# IMPORTANT: Use the exact filename casing as shown in your project tree
RESOURCES += \
    Resources.qrc # Capital 'R' matches your screenshot

# Default rules for deployment (usually added by Qt Creator)
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
