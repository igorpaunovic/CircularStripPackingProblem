QT       += core gui opengl charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
LIBS += -lglut -lGLU
CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    algoritambaza.cpp \
    animacijanit.cpp \
    circularstrippacking.cpp \
    krug.cpp \
    main.cpp \
    mainwindow.cpp \
    oblastcrtanja.cpp \
    oblastcrtanjaopengl.cpp \
    pomocnefunkcije.cpp \
    timemeasurementthread.cpp \
    ugaonapozicija.cpp

HEADERS += \
    algoritambaza.h \
    animacijanit.h \
    circularstrippacking.h \
    config.h \
    krug.h \
    mainwindow.h \
    oblastcrtanja.h \
    oblastcrtanjaopengl.h \
    pomocnefunkcije.h \
    timemeasurementthread.h \
    tomsolver.h \
    ugaonapozicija.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += /usr/include/eigen3

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
