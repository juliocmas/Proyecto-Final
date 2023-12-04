#include "label.h"
#include "nivel2.h"
#include <QString>
#include <QImage>
#include <QRect>
#include <QPainter>

// Constructor de la clase Label
Label::Label(Nivel2 *host)
{
    _host = host;
    _cuadros = host->cuadros();
}

// Devuelve la firma de Label
QString Label::signature()
{
    return QString("Label");
}

// Verifica si el Label es visible
bool Label::is_visible()
{
    return _is_visible;
}

// Método para generar un nuevo Label en las coordenadas dadas
void Label::spawn(int x, int y)
{
    // Verifica si los puntos de generación están libres
    bool spawnpoints_are_free = true;
    int width = _cuadros->width() * 5;
    int height = _cuadros->height() * 5;
    for (int i = y; i < y + _height_px && spawnpoints_are_free; i += 5) {
        for (int j = x; j < x + _width_px && spawnpoints_are_free; j += 5) {
            if (!((0 <= i && i < height) || (0 <= j && j < width))
                || _cuadros->is_owned(j / 5, i / 5)) {
                spawnpoints_are_free = false;
            }
        }
    }
    // Si los puntos de generación están libres, coloca el Label en ellos
    if (spawnpoints_are_free) {
        for (int i = y; i < y + _height_px && spawnpoints_are_free; i += 5) {
            for (int j = x; j < x + _width_px && spawnpoints_are_free; j += 5) {
                this->_cuadros->own(j / 5, i / 5, this);
            }
        }
        _x = x;
        _y = y;
        _is_visible = true;
    }
}

// Método para realizar acciones del Label en el juego (actualmente no realiza ninguna acción)
void Label::act()
{
    // No realiza acciones en este momento
}

// Método para manejar la muerte del Label
void Label::die()
{
    for (int i = _y; i < _y + _height_px; i += 5) {
        for (int j = _x; j < _x + _width_px; j += 5) {
            _cuadros->free(j / 5, i / 5);
        }
    }
    _is_visible = false;
}

// Obtiene la posición x del Label
int Label::x()
{
    return _x;
}

// Obtiene el ancho del Label
int Label::width()
{
    return _width_px;
}

// Obtiene la posición y del Label
int Label::y()
{
    return _y;
}

// Obtiene la altura del Label
int Label::height()
{
    return _height_px;
}

// Obtiene el valor del Label
int Label::value()
{
    return _value;
}

// Establece la geometría del Label (ancho y alto)
void Label::set_geometry(int width, int height)
{
    _width_px = width;
    _height_px = height;
}

// Establece el texto del Label
void Label::set_text(QString text)
{
    _text = text;
}

// Establece el valor del Label
void Label::set_value(int value)
{
    _value = value;
}

// Dibuja el Label en el QPainter proporcionado
void Label::draw(QPainter *painter)
{
    // Dibuja el Label solo si es visible y tiene texto
    if (_text.size() > 0 && _is_visible) {
        painter->save();

        // Concatena el texto y el valor para mostrar
        QString display_text = _text + ": " + QString::number(_value);

        // Configura la fuente del pintor para el texto
        QFont font = painter->font();
        font.setPointSize(font.pointSize() * 3);
        painter->setFont(font);

        // Dibuja el texto en la posición y dimensiones del Label
        painter->drawText(_x, _y, _width_px, _height_px, 0, display_text);

        painter->restore();
    }
}
