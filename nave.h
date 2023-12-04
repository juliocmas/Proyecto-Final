#ifndef NAVE_H
#define NAVE_H

#include "juegobject.h"
#include <QString>
class Nivel2;
class Cuadros;
class QPainter;

class Nave : public JuegObject
{
public:
    Nave(Nivel2* host);

    QString signature();

    bool is_visible();

    void spawn(int x, int y);
    void act();
    void move(); // El movimiento ya es posible
    void die();

    bool can_shoot();
    void give_ammo();

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

    bool _can_shoot = false;
    bool _is_visible = false;
    int _x;
    int _y;
    int _dx = 0;
    int _dy = 2;
    QString _speed_mode = "down_to_right";
    int _speed_change_cd = 0;
};

#endif // NAVE_H

