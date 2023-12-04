#include "disparo.h"
#include "nivel2.h"
#include <QString>
#include <QImage>
#include <QRect>
#include <QPainter>

Disparo::Disparo(Nivel2* host)
{
    _host = host;
    _cuadros = host->cuadros();
}

QString Disparo::signature()
{
    return QString("Disparo");
}

bool Disparo::is_visible()
{
    return _is_visible;
}

void Disparo::spawn(int x, int y)
{
    // Verificar si los puntos de generación están libres
    bool spawnpoints_are_free = true;
    int width = _cuadros->width() * 5;
    int height = _cuadros->height() * 5;

    for (int i = y; i < y + _HEIGHT_PX && spawnpoints_are_free; i += 5) {
        for (int j = x; j < x + _WIDTH_PX && spawnpoints_are_free; j += 5) {
            if (!((0 <= i && i < height) || (0 <= j && j < width)) || _cuadros->is_owned(j / 5, i / 5)) {
                spawnpoints_are_free = false;
            }
        }
    }

    // Si los puntos de generación están libres, ocuparlos en la cuadrícula
    if (spawnpoints_are_free) {
        for (int i = y; i < y + _HEIGHT_PX && spawnpoints_are_free; i += 5) {
            for (int j = x; j < x + _WIDTH_PX && spawnpoints_are_free; j += 5) {
                this->_cuadros->own(j / 5, i / 5, this);
            }
        }
        _x = x;
        _y = y;
        _is_visible = true;
    }
}

void Disparo::act()
{
    // Intentar mover hacia arriba y manejar colisiones o autodestrucción al chocar con el techo
    bool move_space_is_free = true;
    JuegObject* owner;
    int newx = _x + _dx, newy = _y + _dy;

    for (int i = newy; i < newy + _HEIGHT_PX && move_space_is_free; i += 5) {
        for (int j = newx; j < newx + _WIDTH_PX && move_space_is_free; j += 5) {
            if (!(_cuadros->is_free(j / 5, i / 5) || _cuadros->owner(j / 5, i / 5) == this)) {
                move_space_is_free = false;
                owner = _cuadros->owner(j / 5, i / 5);
            }
        }
    }

    // Si el espacio de movimiento está libre, mover la nave
    if (move_space_is_free) {
        this->move();
    }
    else {
        QVector<JuegObject*> collision_info;
        collision_info.append(this);
        collision_info.append(owner);
        _host->recieve_message("collision", collision_info);
    }
}

void Disparo::move()
{
    // Liberar la cuadrícula en la posición actual y ocuparla en la nueva posición
    for (int i = _y; i < _y + _HEIGHT_PX; i += 5) {
        for (int j = _x; j < _x + _WIDTH_PX; j += 5) {
            _cuadros->free(j / 5, i / 5);
            _cuadros->own((j + _dx) / 5, (i + _dy) / 5, this);
        }
    }
    _x += _dx;
    _y += _dy;
}

void Disparo::die()
{
    // Liberar la cuadrícula en la posición actual y hacer invisible la nave
    for (int i = _y; i < _y + _HEIGHT_PX; i += 5) {
        for (int j = _x; j < _x + _WIDTH_PX; j += 5) {
            _cuadros->free(j / 5, i / 5);
        }
    }
    _is_visible = false;
}

int Disparo::x()
{
    return _x;
}

int Disparo::width()
{
    return _WIDTH_PX;
}

int Disparo::y()
{
    return _y;
}

int Disparo::height()
{
    return _HEIGHT_PX;
}

void Disparo::draw(QPainter* painter)
{
    // Dibujar la nave si es visible
    if (_is_visible) {
        QImage sprite(QString(":/disparo.png"));
        painter->drawImage(QRect(_x, _y, _WIDTH_PX, _HEIGHT_PX), sprite);
    }
}
