
QT += core gui sql widgets
QT += core gui widgets sql printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clientdashboardwidget.cpp \
    clientpaymentwidget.cpp \
    connection.cpp \
    createeditinvoicedialog.cpp \
    deleteinvoicedialog.cpp \
    invoicelineitem.cpp \
    invoicemanagementwidget.cpp \
    invoices.cpp \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp

HEADERS += \
    clientdashboardwidget.h \
    clientpaymentwidget.h \
    connection.h \
    createeditinvoicedialog.h \
    deleteinvoicedialog.h \
    invoicelineitem.h \
    invoicemanagementwidget.h \
    invoices.h \
    mainwindow.h \
    settingsdialog.h

FORMS += \
    clientdashboardwidget.ui \
    clientpaymentwidget.ui \
    createeditinvoicedialog.ui \
    deleteinvoicedialog.ui \
    invoicemanagementwidget.ui \
    mainwindow.ui \
    settingsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    style.qss

RESOURCES += \
    Resources.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
