#ifndef CARACTER_H
#define CARACTER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QString>

class Caracter: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Caracter(QString imagePath, int** boardData, int r, int c);
    void setDirection(int d);
    void setPosition(int r, int c);
    void updateImage(QString imagePath);

    enum movements{up, down, right, left};
    virtual bool validMovement(movements movement) = 0;

    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();

    virtual void returnHome() = 0;

    int getData();
    int getData(int r, int c);

    void getPosition(int current, int& r, int& c);
protected:
    int row, col;
private:
    int **data, direction;
};

#endif // CARACTER_H
