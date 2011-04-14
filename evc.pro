TEMPLATE = lib
QT -= gui

CONFIG += warn_on plugin
CONFIG -= thread exceptions rtti

DEFINES +=  XPLM200
VERSION = 1.0.0
OBJECTS_DIR = objects
DESTDIR = plugin

win32 {
    INCLUDEPATH += ../../SDK/CHeaders/XPLM
    DEFINES += LIN=0 IBM=1 APL=0
    TARGET = win.xpl
    LIBS += -L../../SDK/Libraries/Win -lXPLM
}

unix:!macx {
    INCLUDEPATH += ../../../SDK/CHeaders/XPLM
    DEFINES += LIN=1 IBM=0 APL=0
    TARGET = lin.xpl
    QMAKE_LFLAGS += -g -Wl,-rpath,\\\$\$ORIGIN/liblinux/
}

macx {
    INCLUDEPATH += ../../SDK/CHeaders/XPLM
    DEFINES += APL=1 IBM=0 LIN=0
    TARGET = mac.xpl
    QMAKE_CXXFLAGS += -m32
    QMAKE_LFLAGS += -m32 -flat_namespace -undefined suppress

    # Build for multiple architectures.
    # The following line is only needed to build universal on PPC architectures.
    # QMAKE_MAC_SDK=/Developer/SDKs/MacOSX10.4u.sdk
    # The following line defines for which architectures we build.
    CONFIG += x86
}

# Input
HEADERS += \
    Library/FMS/airport.h \
    Library/FMS/airway.h \
    Library/FMS/approach.h \
    Library/FMS/basics.h \
    Library/FMS/flightroute.h \
    Library/FMS/holding.h \
    Library/FMS/icaoroute.h \
    Library/FMS/ils.h \
    Library/FMS/intersection.h \
    Library/FMS/MProjection.h \
    Library/FMS/navcalc.h \
    Library/FMS/ndb.h \
    Library/FMS/procedure.h \
    Library/FMS/projection_greatcircle.h \
    Library/FMS/ptrlist.h \
    Library/FMS/route.h \
    Library/FMS/runway.h \
    Library/FMS/sid.h \
    Library/FMS/star.h \
    Library/FMS/transition.h \
    Library/FMS/vor.h \
    Library/FMS/waypoint.h \
    Library/FMS/waypoint_hdg_to_alt.h \
    Library/FMS/waypoint_hdg_to_intercept.h \
    Library/Dataref/DFloat.h \
    Library/Dataref/DInteger.h \
    Library/Dataref/DFloatArray.h \
    Library/Dataref/DIntegerArray.h \
    Systems/FMS/FMSData.h \
    Systems/FMS/FMSDatabase.h \
    Systems/FMS/FMSIRS.h \
    Systems/FMS/FMSPad.h \
    Systems/FMS/FMSPref.h \
    Systems/FMS/FMSSystem.h \
    vascommands.h

SOURCES += \
    Library/FMS/airport.cpp \
    Library/FMS/airway.cpp \
    Library/FMS/approach.cpp \
    Library/FMS/flightroute.cpp \
    Library/FMS/holding.cpp \
    Library/FMS/icaoroute.cpp \
    Library/FMS/ils.cpp \
    Library/FMS/intersection.cpp \
    Library/FMS/MProjection.cpp \
    Library/FMS/navcalc.cpp \
    Library/FMS/ndb.cpp \
    Library/FMS/procedure.cpp \
    Library/FMS/projection_greatcircle.cpp \
    Library/FMS/route.cpp \
    Library/FMS/runway.cpp \
    Library/FMS/sid.cpp \
    Library/FMS/star.cpp \
    Library/FMS/transition.cpp \
    Library/FMS/vor.cpp \
    Library/FMS/waypoint.cpp \
    Library/tinyxml/tinystr.cpp \
    Library/tinyxml/tinyxml.cpp \
    Library/tinyxml/tinyxmlparser.cpp \
    Library/tinyxml/tinyxmlerror.cpp \
    Systems/FMS/FMSDatabase.cpp \
    Systems/FMS/FMSIRS.cpp \
    Systems/FMS/FMSPad.cpp \
    Systems/FMS/FMSPref.cpp \
    Systems/FMS/FMSSystem.cpp
