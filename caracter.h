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
    // Constructor de la clase Caracter.
    // imagePath: ruta de la imagen del personaje.
    // boardData: datos del tablero.
    // r, c: posición inicial en filas y columnas.
    Caracter(QString imagePath, int** boardData, int r, int c);

    // Establece la dirección del personaje.
    void setDirection(int d);

    // Establece la posición del personaje en filas y columnas.
    void setPosition(int r, int c);

    // Actualiza la imagen del personaje.
    void updateImage(QString imagePath);

    // Enumerador que representa las posibles direcciones de movimiento.
    enum movements{up, down, right, left};

    // Función virtual pura que debe ser implementada por clases derivadas.
    virtual bool validMovement(movements movement) = 0;

    // Métodos para mover el personaje en diferentes direcciones.
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();

    // Función virtual pura que debe ser implementada por clases derivadas.
    virtual void returnHome() = 0;

    // Obtiene los datos del personaje.
    int getData();

    // Obtiene los datos del tablero en la posición especificada.
    int getData(int r, int c);

    // Obtiene la posición actual del personaje.
    void getPosition(int current, int& r, int& c);

protected:
    // Variables miembro protegidas.
    int row, col;

private:
    // Variables miembro privadas.
    int **data, direction;
};

#endif // CARACTER_H
