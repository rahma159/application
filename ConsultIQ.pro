
QT += core gui widgets sql printsupport network
QT += charts



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
    invoicemanagementwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    statisticsdialog.cpp

HEADERS += \
    clientdashboardwidget.h \
    clientpaymentwidget.h \
    connection.h \
    createeditinvoicedialog.h \
    deleteinvoicedialog.h \
    invoicemanagementwidget.h \
    mainwindow.h \
    settingsdialog.h \
    statisticsdialog.h


FORMS += \
    clientdashboardwidget.ui \
    clientpaymentwidget.ui \
    createeditinvoicedialog.ui \
    deleteinvoicedialog.ui \
    invoicemanagementwidget.ui \
    mainwindow.ui \
    settingsdialog.ui \
    statisticsdialog.ui


DISTFILES += \
    style.qss

RESOURCES += \
    Resources.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

CONFIG(release, debug|release):CONFIG -= sanitizer address_sanitizer
