QT += core gui widgets printsupport

CONFIG += c++11

TARGET = Keithley_2002_1.3.2
TEMPLATE = app

include(gpib488_1/gpibAgilent.pri)
#include(gpib488_1/gpibAdvantech.pri)

#include(gpib488_2/gpibAgilent.pri)
#include(gpib488_2/gpibAdvantech.pri)

SOURCES += main.cpp \
           mainwindow.cpp \
           qcustomplot.cpp

HEADERS += \
           mainwindow.h \
           qcustomplot.h

FORMS += mainwindow.ui

RESOURCES += \
             resource.qrc
