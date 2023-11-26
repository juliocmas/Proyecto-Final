#include "rick.h"

// Constructor de la clase Rick
Rick::Rick(int** boardData, int level, int index): Caracter("rick.png", boardData, 14, 8)
{
    // Configurar identificador y posición inicial según el índice
    id = index;
    switch(id)
    {
    case 1: setPosition(1,8);break;
    case 2: setPosition(8,14);break;
    case 3: setPosition(8,1);break;
    }

    // Configurar el tiempo de movimiento según el nivel
    switch(level)
    {
    case 0: time = 400;break;
    case 1: time = 300;break;
    case 2: time = 200;break;
    }

    pathIndex = 0;
    map = new Map(boardData);

    // Calcular la ruta más corta hacia el objetivo según el índice
    switch(index)
    {
    case 0: path = map->calculateShortestPath(getData(), 67);break;
    case 1: path = map->calculateShortestPath(getData(), 47);break;
    case 2: path = map->calculateShortestPath(getData(), 58);break;
    case 3: path = map->calculateShortestPath(getData(), 74);break;
    }
}

// Método para devolver a Rick a su posición inicial
void Rick::returnHome()
{
    switch(id)
    {
    case 0: setPosition(14,8);break;
    case 1: setPosition(1,8);break;
    case 2: setPosition(8,14);break;
    case 3: setPosition(8,1);break;
    }
}

// Método para iniciar el movimiento de Rick
void Rick::startMovement()
{
    // Configurar temporizador para llamar a la función de movimiento/slot cada X segundos
    timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()), this, SLOT(move()));
    timer->start(time);
}

// Método para detener el movimiento de Rick
void Rick::stopMovement()
{
    // Detener el temporizador para dejar de llamar a la función de movimiento
    timer->stop();
}

// Método para manejar el movimiento de Rick
void Rick::move()
{
    int newRow, newCol;
    if(pathIndex<path.size())
    {
        getPosition(path.at(pathIndex), newRow, newCol);
        if(newRow>row)
        {
            moveDown();
        } else if(newRow<row) {
            moveUp();
        } else if(newCol>col) {
            moveRight();
        } else if(newCol<col) {
            moveLeft();
        }
        setPosition(row, col);
        pathIndex++;
    }
    // Verificar colisiones con objetos
    QList<QGraphicsItem *> colliding = collidingItems();
    for(QList<QGraphicsItem*>::iterator i = colliding.begin(); i!=colliding.end(); i++)
    {
        if(typeid(**i)==typeid(Prime))
        {
            // Atrapar a Prime
            Prime* prime = qgraphicsitem_cast<Prime*>(*i);
            prime->catchMe();
        }
    }
}

// Método para cambiar el objetivo de Rick
void Rick::changeTarget()
{
    Prime* prime = static_cast<Prime*>(sender());
    path = map->calculateShortestPath(this->getData(), prime->getData());
    pathIndex = 0;
}

// Método para verificar si el movimiento es válido para Rick
bool Rick::validMovement(movements movement)
{
    if((movement == up && getData(row-1, col) >= 0)
        || (movement == down && getData(row+1, col) >= 0)
        || (movement == right && getData(row, col+1) >= 0)
        || ((movement == left && getData(row, col-1) >= 0)) )
        return true;

    return false;
}
