#ifndef RICK_H
#define RICK_H

#include <QTimer>
#include <QList>
#include <QVector>
#include "caracter.h"
#include "prime.h"
#include "map.h"
#include "time.h"
#include "stdlib.h"


class Rick: public Caracter
{
    Q_OBJECT
public:
    Rick(int** boardData, int level, int index);
    virtual void returnHome();
    void startMovement();
    void stopMovement();
    virtual bool validMovement(movements movement);
public slots:
    void move();
    void changeTarget();
private:
    Map* map;
    QVector<int> path;
    int pathIndex;
    int time, id;
    QTimer* timer;
};

#endif // RICK_H
