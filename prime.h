#ifndef PRIME_H
#define PRIME_H

#include <QKeyEvent>
#include <QGraphicsScene>
#include "caracter.h"
#include "powerup.h"
#include "pistolitem.h"
#include "rick.h"

class Prime: public Caracter
{
    Q_OBJECT
public:
    Prime(int** boardData);
    void catchMe();
    void powerUp();
    void carryPistol(PistolItem* pistol);
    void dropPistol();
    bool hasPistol();
    bool hasPowerUp();
    bool atHome();
    virtual bool validMovement(movements movement);
    virtual void returnHome();
    void reachedHome();
public slots:
    void powerDown();
    void keyPressEvent(QKeyEvent* event);
signals:
    void decreasePistolCounter();
    void decreaseHealthCounter();
    void endGame();
    void winGame();
    void changeMotion();
private:
    int lifes, countCollectedPistol;
    bool poweredUp, carryingPistol;
    PistolItem* carriedPistol;
};

#endif // PRIME_H
