#include "nave.h"
#include "nivel2.h"
#include <QString>
#include <QImage>
#include <QRect>
#include <QPainter>
#include <ctime>
//std::srand(std::time(nullptr));

// Constructor de la clase Nave
Nave::Nave(Nivel2* host)
{
    _host = host;
    _cuadros = host->cuadros();
}

// Devuelve la firma de Nave
QString Nave::signature()
{
    return QString("Nave");
}

// Verifica si el Nave es visible
bool Nave::is_visible()
{
    return _is_visible;
}

// Método para generar un nuevo Nave en las coordenadas dadas
void Nave::spawn(int x, int y)
{
    // Verifica si los puntos de generación están libres
    bool spawnpoints_are_free = true;
    int width = _cuadros->width() * 5;
    int height = _cuadros->height() * 5;
    for (int i = y; i < y + _HEIGHT_PX && spawnpoints_are_free; i += 5) {
        for (int j = x; j < x + _WIDTH_PX && spawnpoints_are_free; j += 5) {
            if (!((0 <= i && i < height) || (0 <= j && j < width))
                || _cuadros->is_owned(j / 5, i / 5)) {
                spawnpoints_are_free = false;
            }
        }
    }
    // Si los puntos de generación están libres, coloca el Nave en ellos
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

// Método para realizar acciones del Nave en el juego
void Nave::act()
{
    // Intento de movimiento: actualización del cooldown para cambiar la velocidad
    if (_speed_change_cd == 0) {
        if (_speed_mode == "right") {
            _speed_mode = "down_to_left";
            _dx = 0;
            _dy = 5;
            _speed_change_cd = 12;
        }
        else if (_speed_mode == "down_to_left") {
            _speed_mode = "left";
            _dx = -5;
            _dy = 0;
            _speed_change_cd = 30;
        }
        else if (_speed_mode == "left") {
            _speed_mode = "down_to_right";
            _dx = 0;
            _dy = 5;
            _speed_change_cd = 12;
        }
        else if (_speed_mode == "down_to_right") {
            _speed_mode = "right";
            _dx = 5;
            _dy = 0;
            _speed_change_cd = 30;
        }
    }
    // Si el cooldown para cambiar la velocidad no ha pasado
    else {
        --_speed_change_cd;
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
        // Si el espacio de movimiento está libre, mueve el Nave
        if (move_space_is_free) {
            this->move();
        }
        // Si hay una colisión, envía un mensaje de colisión al motor del juego
        else {
            QVector <JuegObject*> collision_info;
            collision_info.append(this);
            collision_info.append(owner);
            _host->recieve_message("collision", collision_info);
        }
    }
    // Posiblemente dispara, pero no es seguro
    int shoot_coin_toss = std::rand() % 80;
    if (shoot_coin_toss == 0) {
        QVector <JuegObject*> shoot_info;
        shoot_info.append(this);
        _host->recieve_message("shoot", shoot_info);
    }
}

// Método para mover el Nave
void Nave::move()
{
    for (int i = _y; i < _y + _HEIGHT_PX; i += 5) {
        for (int j = _x; j < _x + _WIDTH_PX; j += 5) {
            _cuadros->free(j / 5, i / 5);
            _cuadros->own((j + _dx) / 5, (i + _dy) / 5, this);
        }
    }
    _x += _dx;
    _y += _dy;
}

// Método para manejar la muerte del Nave
void Nave::die()
{
    for (int i = _y; i < _y + _HEIGHT_PX; i += 5) {
        for (int j = _x; j < _x + _WIDTH_PX; j += 5) {
            _cuadros->free(j / 5, i / 5);
        }
    }
    _is_visible = false;
}

// Verifica si el Nave puede disparar
bool Nave::can_shoot()
{
    return _can_shoot;
}

// Otorga munición al Nave
void Nave::give_ammo()
{
    _can_shoot = true;
}

// Obtiene la posición x del Nave
int Nave::x()
{
    return _x;
}

// Obtiene el ancho del Nave
int Nave::width()
{
    return _WIDTH_PX;
}

// Obtiene la posición y del Nave
int Nave::y()
{
    return _y;
}

// Obtiene la altura del Nave
int Nave::height()
{
    return _HEIGHT_PX;
}

// Dibuja el Nave en el QPainter proporcionado
void Nave::draw(QPainter* painter)
{
    if (_is_visible) {
        QImage sprite(QString("nave.png"));
        painter->drawImage(QRect(_x, _y, _WIDTH_PX, _HEIGHT_PX), sprite);
    }
}
