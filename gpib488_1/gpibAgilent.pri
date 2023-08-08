#
# gpibAgilent.pri
# ITT, ORE, I.Mitrofanov
# 2017-07-11
#

INCLUDEPATH += \
	$$PWD \
	$$PWD/agilent

#DEPENDPATH += $$PWD

LIBS += \
	$$PWD/agilent/gpib-32.obj

HEADERS += \
	$$PWD/GPIBPort.h \
	$$PWD/agilent/ni488.h

SOURCES += \
	$$PWD/GPIBAgilentPort.cpp
