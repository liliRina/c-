QT       += core gui
QT +=opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core/cEci.cpp \
    core/cJulian.cpp \
    core/cSite.cpp \
    core/cTLE.cpp \
    core/cVector.cpp \
    core/coord.cpp \
    core/globals.cpp \
    core/stdafx.cpp \
    main.cpp \
    mainwindow.cpp \
    miwidget.cpp \
    orbit/cNoradBase.cpp \
    orbit/cNoradSDP4.cpp \
    orbit/cNoradSGP4.cpp \
    orbit/cOrbit.cpp \
    orbit/cSatellite.cpp \
    orbit/stdafx.cpp \
    world.cpp \
    worldobject.cpp

HEADERS += \
    core/cEci.h \
    core/cJulian.h \
    core/cSite.h \
    core/cTLE.h \
    core/cVector.h \
    core/coord.h \
    core/coreLib.h \
    core/exceptions.h \
    core/globals.h \
    core/stdafx.h \
    mainwindow.h \
    miwidget.h \
    orbit/cNoradBase.h \
    orbit/cNoradSDP4.h \
    orbit/cNoradSGP4.h \
    orbit/cOrbit.h \
    orbit/cSatellite.h \
    orbit/orbitLib.h \
    orbit/stdafx.h \
    world.h \
    worldobject.h

FORMS += \
    mainwindow.ui
LIBS += -lOpengl32
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    core/core.vcxproj \
    core/core.vcxproj.filters \
    core/revHistory.txt \
    orbit/orbit.vcxproj \
    orbit/orbit.vcxproj.filters \
    orbit/revHistory.txt
