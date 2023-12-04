#ifndef NESPACIAL_H
#define NESPACIAL_H

#include "juegobject.h"
#include <QString>
class Nivel2;
class Cuadros;
class QPainter;

class Nespacial : public JuegObject
{
public:
    Nespacial(Nivel2* host);

    QString signature();

    bool is_visible();

    void spawn(int x, int y);
    void act();
    void move(); // El movimiento ya es posible
    void die();

    int x();
    int width();
    int y();
    int height();

    void draw(QPainter* painter);

private:
    Nivel2* _host;
    Cuadros* _cuadros;

    int _WIDTH_PX = 60;
    int _HEIGHT_PX = 60;
    int _SHOOT_CD_MAX = 10;

    bool _is_visible = false;
    int _x;
    int _y;
    int _dx = 0;
    int _dy = 0;
    int _shoot_cd = 0;
};

#endif // NESPACIAL_H
