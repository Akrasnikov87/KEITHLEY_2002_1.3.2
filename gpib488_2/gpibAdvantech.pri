#
# gpibAdvantech.pri
# ITT, ORE, I.Mitrofanov
# 2017-07-11
#

INCLUDEPATH += $$PWD $$PWD/advantech
#DEPENDPATH += $$PWD

LIBS += $$PWD/advantech/gpib488.obj

HEADERS += $$PWD/GPIBPort.h $$PWD/advantech/gpib488.h
SOURCES += $$PWD/GPIBAdvantechPort.cpp
