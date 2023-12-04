#ifndef JUEGOSCREEN_H
#define JUEGOSCREEN_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QElapsedTimer>
#include "rick.h"
#include "prime.h"
#include "pistolitem.h"
#include "powerup.h"
#include "contadorinicio.h"
#include "finaljuego.h"
#include "map.h"
#include "user.h"
#include "mainwindow.h"
#include "nivel2.h"

class JuegoScreen: public QGraphicsView
{
    Q_OBJECT
public:
    JuegoScreen(int level, int ricks, User &account);
    ContadorInicio *HealthLabel, *PistolLabel;
public slots:
    void gameOver();
    void win();
private:
    QElapsedTimer gameTimer;
    QGraphicsScene* scene;
    PistolItem* pistols[4];
    PowerUp* powerUps[2];
    int** data;
    int rickCounter;
    Rick** rick;
    Prime* prime;
    User currentUser;
};

#endif // JUEGOSCREEN_H
