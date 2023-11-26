#include "prime.h"

// Constructor de la clase Prime
Prime::Prime(int** boardData): Caracter("primeNormal.png",boardData,7,7)
{
    // Inicializar variables
    lifes = 3;
    countCollectedPistol = 0;
    poweredUp = false;
    carryingPistol = false;
    carriedPistol = NULL;
}

// Método para manejar la pérdida de vidas de Prime
void Prime::catchMe()
{
    // Primero verifica que Prime no esté potenciado
    if(!poweredUp)
    {
        // Decrementar vidas
        lifes--;

        // Decrementar contador en la etiqueta
        emit decreaseHealthCounter();

        // Verificar si el juego ha terminado
        if(lifes == 0)
        {
            emit endGame();
            return;
        }

        // Verificar si Prime está llevando una pistola
        if(hasPistol())
            dropPistol();

        // Devolver tanto a Prime como a Rick a sus posiciones iniciales
        // Devolver a Rick a su posición inicial
        QList<QGraphicsItem *> colliding = collidingItems();
        // Localizar el objeto de Rick
        for(QList<QGraphicsItem*>::iterator i = colliding.begin(); i!=colliding.end(); i++)
        {
            if(typeid(**i) == typeid(Rick))
            {
                Rick* rick = qgraphicsitem_cast<Rick*>(*i);
                rick->returnHome();
            }
        }
        // Devolver a Prime a su posición inicial
        returnHome();
    }
}

// Método para activar la potenciación de Prime
void Prime::powerUp()
{
    // Actualizar estado
    poweredUp = true;

    // Actualizar avatar de Prime
    // Verificar si lleva pistola o no
    if(hasPistol())
        updateImage("primeStrongPistol.png");
    else
        updateImage("primeStrong.png");
}

// Método para desactivar la potenciación de Prime
void Prime::powerDown()
{
    // Actualizar estado
    poweredUp = false;

    // Actualizar avatar de Prime
    if(hasPistol())
        updateImage("primeNormalPistol.png");
    else
        updateImage("primeNormal.png");
}

// Método para verificar si Prime está potenciado
bool Prime::hasPowerUp()
{
    return poweredUp;
}

// Método para verificar si Prime lleva una pistola
bool Prime::hasPistol()
{
    return carryingPistol;
}

// Método para que Prime lleve una pistola
void Prime::carryPistol(PistolItem* pistol)
{
    // Verificar primero si ya está llevando una pistola
    if(!hasPistol())
    {
        carryingPistol = true;
        // Almacenar la pistola
        carriedPistol = pistol;
        // Quitar la pistola de la escena
        scene()->removeItem(carriedPistol);

        // Actualizar avatar de Prime
        // Verificar si Prime tiene una potenciación o no
        if(hasPowerUp())
            updateImage("primeStrongPistol.png");
        else
            updateImage("primeNormalPistol.png");
    }
}

// Método para que Prime deje caer la pistola
void Prime::dropPistol()
{
    // Verificar primero si ya está llevando una pistola
    if(hasPistol())
    {
        // Volver a agregar la pistola a la escena
        scene()->addItem(carriedPistol);
        // Quitar la pistola llevada
        carriedPistol = NULL;
        carryingPistol = false;
        // Cambiar el avatar de Prime a sin pistola
        if(hasPowerUp())
            updateImage("primeStrong.png");
        else
            updateImage("primeNormal.png");
    }
}

// Método para cuando Prime llega a casa
void Prime::reachedHome()
{
    // Verificar si lleva una pistola para recogerla exitosamente
    if(hasPistol())
    {
        // Incrementar el número de pistolas recogidas
        countCollectedPistol++;

        switch(countCollectedPistol)
        {
        case 1: carriedPistol->setPosition(7, 7); break;
        case 2: carriedPistol->setPosition(7, 8); break;
        case 3: carriedPistol->setPosition(8, 7); break;
        case 4: carriedPistol->setPosition(8, 8); break;
        }

        // Agregar la pistola con posición actualizada a la escena
        scene()->addItem(carriedPistol);

        // Actualizar la etiqueta de conteo
        emit decreasePistolCounter();

        // Vaciar carriedPistol
        carriedPistol = NULL;

        carryingPistol = false;

        if(hasPowerUp())
            updateImage("primeStrong.png");
        else
            updateImage("primeNormal.png");

        // Verificar si se recogieron las 4 pistolas
        if(countCollectedPistol == 4)
            emit winGame();
    }
}

// Manejar eventos de teclas presionadas para Prime
void Prime::keyPressEvent(QKeyEvent* event)
{
    // Mover al jugador según la tecla presionada si se suministra un movimiento válido
    if(event->key() == Qt::Key_Up && validMovement(up))
    {
        moveUp();
        emit changeMotion();
    }
    else if(event->key() == Qt::Key_Down && validMovement(down))
    {
        moveDown();
        emit changeMotion();
    }
    else if(event->key() == Qt::Key_Right && validMovement(right))
    {
        moveRight();
        emit changeMotion();
    }
    else if(event->key() == Qt::Key_Left && validMovement(left))
    {
        moveLeft();
        emit changeMotion();
    }

    // Verificar si Prime llegó a el centro del laberinto
    if(atHome())
        reachedHome();

    // Verificar colisiones con objetos
    QList<QGraphicsItem *> colliding = collidingItems();
    for(QList<QGraphicsItem*>::iterator i = colliding.begin(); i!=colliding.end(); i++)
    {
        // Verificar colisión con objeto Power Up
        if(typeid(**i)==typeid(PowerUp))
        {
            // Quitar Power Up de la escena
            scene()->removeItem(*i);
            // Potenciar a Prime
            powerUp();
            // Configurar un temporizador para quitar el efecto de potenciación después de 10 segundos
            QTimer::singleShot(10000, this, SLOT(powerDown()));
        }

        // Verificar colisión con objeto Pistol
        else if(typeid(**i) == typeid(PistolItem))
        {
            // Asegurarse de que Prime no esté tomando una pistola guardada en laberinto
            if(!atHome())
                carryPistol(qgraphicsitem_cast<PistolItem*>(*i));
        }

        // Verificar colisión con objeto Rick
        else if(typeid(**i) == typeid(Rick))
        {
            catchMe();
        }
    }
}

// Método para devolver a Prime en el centro del laberinto
void Prime::returnHome()
{
    setPosition(7,7);
    emit changeMotion();
}

// Método para verificar si Prime está en el centro del Laberinto
bool Prime::atHome()
{
    return (row>=7 && row<=8 && col>=7 && col<=8);
}

// Método para verificar si el movimiento es válido para Prime
bool Prime::validMovement(movements movement)
{
    if((movement == up && (getData(row-1, col) >= 0 || getData(row-1, col) == -20))
        || (movement == down && (getData(row+1, col) >= 0 || getData(row+1, col) == -20))
        || (movement == right && (getData(row, col+1) >= 0|| getData(row, col+1) == -20))
        || (movement == left && (getData(row, col-1) >= 0 || getData(row, col-1) == -20)))
        return true;

    return false;
}
