#include "cuadros.h"
#include "juegobject.h"

// Constructor por defecto, inicializa la cuadrícula con dimensiones predeterminadas 800x600
Cuadros::Cuadros()
    : Cuadros(800, 600) {}

// Constructor que permite especificar las dimensiones de la cuadrícula
Cuadros::Cuadros(int width, int height)
{
    this->_width = width;
    this->_height = height;
    // Inicializa la cuadrícula con un vector bidimensional de punteros a JuegObject
    this->_data = QVector<QVector<JuegObject*>>(height, QVector<JuegObject*>(width, nullptr));
}

// Verifica si la posición en la cuadrícula está libre
bool Cuadros::is_free(int x, int y)
{
    // Devuelve true si no hay ningún objeto en la posición (x, y)
    return !(bool)(this->_data[y][x]);
}

// Verifica si la posición en la cuadrícula está ocupada
bool Cuadros::is_owned(int x, int y)
{
    // Devuelve true si hay un objeto en la posición (x, y)
    return (bool)(this->_data[y][x]);
}

// Obtiene el objeto dueño de la posición en la cuadrícula
JuegObject* Cuadros::owner(int x, int y)
{
    // Devuelve el objeto en la posición (x, y)
    return this->_data[y][x];
}

// Ocupa una posición en la cuadrícula con un objeto dado
void Cuadros::own(int x, int y, JuegObject* object)
{
    // Establece el objeto en la posición (x, y)
    this->_data[y][x] = object;
}

// Libera una posición en la cuadrícula (elimina el objeto de esa posición)
void Cuadros::free(int x, int y)
{
    // Elimina el objeto en la posición (x, y)
    this->_data[y][x] = nullptr;
}

// Devuelve el ancho de la cuadrícula
int Cuadros::width()
{
    return this->_width;
}

// Devuelve la altura de la cuadrícula
int Cuadros::height()
{
    return this->_height;
}
