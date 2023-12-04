// Archivo: juegobject.h
// Clase base para objetos de juego

#include "juegobject.h"
#include <QString>
#include <QPainter>

// Constructor por defecto de la clase JuegObject.
JuegObject::JuegObject()
{

}

// Método que devuelve la firma del objeto de juego.
QString JuegObject::signature()
{
    return QString("");
}

// Método que verifica si el objeto de juego es visible.
bool JuegObject::is_visible()
{
    return false;
}

// Destructor de la clase JuegObject.
JuegObject::~JuegObject()
{

}

// Método que define la acción del objeto de juego en el juego.
void JuegObject::act()
{

}

// Método para generar un nuevo objeto de juego en las coordenadas dadas.
void JuegObject::spawn(int x, int y)
{

}

// Método para manejar la muerte del objeto de juego.
void JuegObject::die()
{

}

// Método para dibujar el objeto de juego en un QPainter proporcionado.
void JuegObject::draw(QPainter* painter)
{

}

// Método que devuelve la posición x del objeto de juego.
int JuegObject::x()
{
    return 0;
}

// Método que devuelve el ancho del objeto de juego.
int JuegObject::width()
{
    return 0;
}

// Método que devuelve la posición y del objeto de juego.
int JuegObject::y()
{
    return 0;
}

// Método que devuelve la altura del objeto de juego.
int JuegObject::height()
{
    return 0;
}


