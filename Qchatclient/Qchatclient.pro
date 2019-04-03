#-------------------------------------------------
#
# Project created by QtCreator 2019-04-03T12:09:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qchatclient
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../spider/logging/target/bin/release/ -llogging
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../spider/logging/target/bin/debug/ -llogging
else:unix: LIBS += -L$$PWD/../spider/logging/target/bin/ -llogging

INCLUDEPATH += $$PWD/../spider/logging/src
DEPENDPATH += $$PWD/../spider/logging/src

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../spider/translayor/target/lib/release/ -ltranslayor
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../spider/translayor/target/lib/debug/ -ltranslayor
else:unix: LIBS += -L$$PWD/../spider/translayor/target/lib/ -ltranslayor

INCLUDEPATH += $$PWD/../spider/translayor/src
DEPENDPATH += $$PWD/../spider/translayor/src
