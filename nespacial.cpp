#include "nespacial.h"
#include "nivel2.h"
#include <QString>
#include <QImage>
#include <QRect>
#include <QPainter>

Nespacial::Nespacial(Nivel2* host)
{
    _host = host;
    _cuadros = host->cuadros();
}

QString Nespacial::signature()
{
    return QString("Nespacial");
}

bool Nespacial::is_visible()
{
    return _is_visible;
}

void Nespacial::spawn(int x, int y)
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

void Nespacial::act()
{
    // Si se presiona una de las teclas de movimiento, moverse
    if (_host->keyboard_state("left") || _host->keyboard_state("right")) {
        if (_host->keyboard_state("left")) {
            _dx = -10;
        }
        else {
            _dx = 10;
        }
        bool move_space_is_free = true;
        JuegObject* owner = nullptr;
        int newx = _x + _dx, newy = _y + _dy;
        int width = _cuadros->width() * 5;

        for (int i = newy; i < newy + _HEIGHT_PX && move_space_is_free; i += 5) {
            for (int j = newx; j < newx + _WIDTH_PX && move_space_is_free; j += 5) {
                // Verificar si se alcanzó el borde de la pantalla
                if (j < 10 || j >= width - 10) {
                    move_space_is_free = false;
                }
                // Verificar si hay colisión con otro objeto en la cuadrícula
                else if (!(_cuadros->is_free(j / 5, i / 5) || _cuadros->owner(j / 5, i / 5) == this)) {
                    move_space_is_free = false;
                    owner = _cuadros->owner(j / 5, i / 5);
                }
            }
        }

        // Si el espacio de movimiento está libre, mover la nave
        if (move_space_is_free) {
            this->move();
        }
        // Si hay colisión con otro objeto, informar al motor del juego
        else if (owner) {
            QVector<JuegObject*> collision_info;
            collision_info.append(this);
            collision_info.append(owner);
            _host->recieve_message("collision", collision_info);
        }
    }

    // Si ha pasado el tiempo de recarga para disparar y la tecla de espacio está presionada, disparar
    if (_shoot_cd > 0) {
        --_shoot_cd;
    }
    else if (_host->keyboard_state("space")) {
        QVector<JuegObject*> shoot_info;
        shoot_info.append(this);
        _host->recieve_message("shoot", shoot_info);
        _shoot_cd = _SHOOT_CD_MAX;
    }
}

void Nespacial::move()
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

void Nespacial::die()
{
    // Liberar la cuadrícula en la posición actual y hacer invisible la nave
    for (int i = _y; i < _y + _HEIGHT_PX; i += 5) {
        for (int j = _x; j < _x + _WIDTH_PX; j += 5) {
            _cuadros->free(j / 5, i / 5);
        }
    }
    _is_visible = false;
}

int Nespacial::x()
{
    return _x;
}

int Nespacial::width()
{
    return _WIDTH_PX;
}

int Nespacial::y()
{
    return _y;
}

int Nespacial::height()
{
    return _HEIGHT_PX;
}

void Nespacial::draw(QPainter* painter)
{
    // Dibujar la nave si es visible
    if (_is_visible) {
        QImage sprite(QString(":/nespacial.png"));
        painter->drawImage(QRect(_x, _y, _WIDTH_PX, _HEIGHT_PX), sprite);
    }
}
