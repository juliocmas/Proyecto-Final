#include "bomba.h"
#include "nivel2.h"
#include <QString>
#include <QImage>
#include <QRect>
#include <QPainter>

Bomba::Bomba(Nivel2* host)
{
    _host = host;
    _Cuadros = host->cuadros();
}

// Devuelve la firma de la Bomba
QString Bomba::signature()
{
    return QString("Bomba");
}

// Verifica si la Bomba es visible
bool Bomba::is_visible()
{
    return _is_visible;
}

// Genera una nueva Bomba en las coordenadas dadas
void Bomba::spawn(int x, int y)
{
    bool spawnpoints_are_free = true;
    int width = _Cuadros->width() * 5;
    int height = _Cuadros->height() * 5;
    for (int i = y; i < y + _HEIGHT_PX && spawnpoints_are_free; i += 5) {
        for (int j = x; j < x + _WIDTH_PX && spawnpoints_are_free; j += 5) {
            if (!((0 <= i && i < height) || (0 <= j && j < width)) || _Cuadros->is_owned(j / 5, i / 5)) {
                spawnpoints_are_free = false;
            }
        }
    }
    if (spawnpoints_are_free) {
        for (int i = y; i < y + _HEIGHT_PX && spawnpoints_are_free; i += 5) {
            for (int j = x; j < x + _WIDTH_PX && spawnpoints_are_free; j += 5) {
                this->_Cuadros->own(j / 5, i / 5, this);
            }
        }
        _x = x;
        _y = y;
        _is_visible = true;
    }
}

// Realiza acciones de la Bomba en el juego
void Bomba::act()
{
    // Intenta moverse hacia abajo y maneja colisiones o autodestrucción al chocar con el suelo
    bool move_space_is_free = true;
    JuegObject* owner;
    int newx = _x + _dx, newy = _y + _dy;
    for (int i = newy; i < newy + _HEIGHT_PX && move_space_is_free; i += 5) {
        for (int j = newx; j < newx + _WIDTH_PX && move_space_is_free; j += 5) {
            if (!(_Cuadros->is_free(j / 5, i / 5) || _Cuadros->owner(j / 5, i / 5) == this)) {
                move_space_is_free = false;
                owner = _Cuadros->owner(j / 5, i / 5);
            }
        }
    }
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

// Mueve la Bomba
void Bomba::move()
{
    for (int i = _y; i < _y + _HEIGHT_PX; i += 5) {
        for (int j = _x; j < _x + _WIDTH_PX; j += 5) {
            _Cuadros->free(j / 5, i / 5);
            _Cuadros->own((j + _dx) / 5, (i + _dy) / 5, this);
        }
    }
    _x += _dx;
    _y += _dy;
}

// Maneja la muerte de la Bomba
void Bomba::die()
{
    for (int i = _y; i < _y + _HEIGHT_PX; i += 5) {
        for (int j = _x; j < _x + _WIDTH_PX; j += 5) {
            _Cuadros->free(j / 5, i / 5);
        }
    }
    _is_visible = false;
}

// Obtiene la posición x de la Bomba
int Bomba::x()
{
    return _x;
}

// Obtiene el ancho de la Bomba
int Bomba::width()
{
    return _WIDTH_PX;
}

// Obtiene la posición y de la Bomba
int Bomba::y()
{
    return _y;
}

// Obtiene la altura de la Bomba
int Bomba::height()
{
    return _HEIGHT_PX;
}

// Dibuja la Bomba en el QPainter proporcionado
void Bomba::draw(QPainter* painter)
{
    if (_is_visible) {
        QImage sprite(QString("Bomba.png"));
        painter->drawImage(QRect(_x, _y, _WIDTH_PX, _HEIGHT_PX), sprite);
    }
}

