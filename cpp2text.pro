#-------------------------------------------------
#
# Project created by QtCreator 2015-06-04T00:02:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cpp2text
TEMPLATE = app


SOURCES += main.cpp\
        converter.cpp \
        mainwindow.cpp

HEADERS  += mainwindow.h \
    converter.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11

isEmpty(PREFIX) {
		PREFIX = /usr
}
target.path = $$PREFIX/bin
INSTALLS += target
