QT += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arco.cpp \
    disco.cpp \
    entidad.cpp \
    juego.cpp \
    jugador.cpp \
    main.cpp \
    mainwindow.cpp \
    mundo.cpp \
    nivel.cpp \
    nivelenfrentamiento.cpp \
    nivelentrenamiento.cpp \
    obstaculo.cpp \
    personaje.cpp \
    rival.cpp \
    vector2d.cpp

HEADERS += \
    arco.h \
    disco.h \
    entidad.h \
    juego.h \
    jugador.h \
    mainwindow.h \
    mundo.h \
    nivel.h \
    nivelenfrentamiento.h \
    nivelentrenamiento.h \
    obstaculo.h \
    personaje.h \
    rival.h \
    vector2d.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    recursos.qrc \

DISTFILES +=
