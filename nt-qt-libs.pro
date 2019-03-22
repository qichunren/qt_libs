#-------------------------------------------------
#
# Project created by QtCreator 2016-11-22T10:12:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nt-qt-libs
TEMPLATE = app


SOURCES += main.cpp\
		mainwindow.cpp gui/tip_label.cpp gui/virtual_keyboard_widget.cpp

HEADERS  += mainwindow.h gui/tip_label.h gui/virtual_keyboard_widget.h

FORMS    += mainwindow.ui gui/virtual_keyboardwidget.ui

OTHER_FILES += README.md
