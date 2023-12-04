#ifndef DISPARO_H
#define DISPARO_H

#include "juegobject.h"
#include <QString>
class Nivel2;
class Cuadros;
class QPainter;

class Disparo : public JuegObject
{
public:
    Disparo(Nivel2* host);

    QString signature();

    bool is_visible();

    void spawn(int x, int y);
    void act();
    void move(); //El movimiento ya es posible
    void die();

    int x();
    int width();
    int y();
    int height();

    void draw(QPainter* painter);

private:
    Nivel2* _host;
    Cuadros* _cuadros;

    int _WIDTH_PX = 20;
    int _HEIGHT_PX = 30;

    bool _is_visible = false;
    int _x;
    int _y;
    int _dx = 0;
    int _dy = -10;
};

#endif // DISPARO_H
