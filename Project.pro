QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


SOURCES += \
    caracter.cpp \
    contadorinicio.cpp \
    finaljuego.cpp \
    iniciojuego.cpp \
    juegoscreen.cpp \
    pistolitem.cpp \
    item.cpp \
    powerup.cpp \
    prime.cpp \
    main.cpp \
    map.cpp \
    rick.cpp \
    tablagamers.cpp \
    user.cpp

HEADERS += \
    caracter.h \
    contadorinicio.h \
    finaljuego.h \
    iniciojuego.h \
    juegoscreen.h \
    pistolitem.h \
    item.h \
    powerup.h \
    prime.h \
    map.h \
    rick.h \
    tablagamers.h \
    user.h

FORMS += \
    finaljuego.ui \
    iniciojuego.ui \
    tablagamers.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    GameResources/GameOver.png \
    GameResources/PrimeWon.png \
    GameResources/blackBackground.jpg \
    GameResources/pistol.png \
    GameResources/edgeCornerBorder.jpg \
    GameResources/head.png \
    GameResources/horizontalBorder.jpg \
    GameResources/primeNormal.png \
    GameResources/primeNormalPistol.png \
    GameResources/primeStrong.png \
    GameResources/primeStrongPistol.png \
    GameResources/leaderBoard.txt \
    GameResources/loseScreen.jpg \
    GameResources/map.txt \
    GameResources/pngegg.png \
    GameResources/powerUp.png \
    GameResources/showsquare.png \
    GameResources/solidBorder.jpg \
    GameResources/tCornerBorder.jpg \
    GameResources/rick.png \
    GameResources/welcomeScreen.jpg \
    GameResources/winScreen.jpg
