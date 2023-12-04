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
    // Constructor de la clase Prime.
    // boardData: datos del tablero.
    Prime(int** boardData);

    // Método para atrapar al personaje Prime.
    void catchMe();

    // Método para activar el power-up del personaje Prime.
    void powerUp();

    // Método para llevar una pistola.
    void carryPistol(PistolItem* pistol);

    // Método para soltar la pistola.
    void dropPistol();

    // Método para verificar si el personaje Prime tiene una pistola.
    bool hasPistol();

    // Método para verificar si el personaje Prime tiene activado el power-up.
    bool hasPowerUp();

    // Método para verificar si el personaje Prime está en su posición inicial.
    bool atHome();

    // Método para verificar si el movimiento en una dirección específica es válido.
    virtual bool validMovement(movements movement);

    // Método para que el personaje Prime regrese a su posición inicial.
    virtual void returnHome();

    // Método para indicar que el personaje Prime ha regresado a su posición inicial.
    void reachedHome();

public slots:
    // Slot para desactivar el power-up después de un tiempo.
    void powerDown();

    // Slot para manejar eventos de teclado.
    void keyPressEvent(QKeyEvent* event);

signals:
    // Señales emitidas en diferentes situaciones del juego.
    void decreasePistolCounter();
    void decreaseHealthCounter();
    void endGame();
    void winGame();
    void changeMotion();

private:
    // Variables miembro privadas para el control del estado del personaje Prime.
    int lifes, countCollectedPistol;
    bool poweredUp, carryingPistol;
    PistolItem* carriedPistol;
};

#endif // PRIME_H
