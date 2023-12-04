QT       += core gui
QT += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


SOURCES += \
    bomba.cpp \
    caracter.cpp \
    contadorinicio.cpp \
    cuadros.cpp \
    disparo.cpp \
    finaljuego.cpp \
    iniciojuego.cpp \
    juegobject.cpp \
    juegoscreen.cpp \
    label.cpp \
    mainwindow.cpp \
    nave.cpp \
    nespacial.cpp \
    nivel2.cpp \
    pistolitem.cpp \
    item.cpp \
    powerup.cpp \
    prime.cpp \
    main.cpp \
    map.cpp \
    rick.cpp \
    user.cpp

HEADERS += \
    bomba.h \
    caracter.h \
    contadorinicio.h \
    cuadros.h \
    disparo.h \
    finaljuego.h \
    iniciojuego.h \
    juegobject.h \
    juegoscreen.h \
    label.h \
    mainwindow.h \
    nave.h \
    nespacial.h \
    nivel2.h \
    pistolitem.h \
    item.h \
    powerup.h \
    prime.h \
    map.h \
    rick.h \
    user.h

FORMS += \
    finaljuego.ui \
    iniciojuego.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    GameResources/GameOver.png \
    GameResources/PrimeWon.png \
    GameResources/blackBackground.jpg \
    GameResources/bomb.png \
    GameResources/invader.png \
    GameResources/pistol.png \
    GameResources/edgeCornerBorder.jpg \
    GameResources/head.png \
    GameResources/horizontalBorder.jpg \
    GameResources/primeNormal.png \
    GameResources/primeNormalPistol.png \
    GameResources/primeStrong.png \
    GameResources/primeStrongPistol.png \
    GameResources/loseScreen.jpg \
    GameResources/map.txt \
    GameResources/pngegg.png \
    GameResources/powerUp.png \
    GameResources/rocket.png \
    GameResources/showsquare.png \
    GameResources/solidBorder.jpg \
    GameResources/spaceship.png \
    GameResources/tCornerBorder.jpg \
    GameResources/rick.png \
    GameResources/welcomeScreen.jpg \
    GameResources/winScreen.jpg

RESOURCES +=
