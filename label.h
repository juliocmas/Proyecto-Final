// Archivo: label.h
// Clase Label para representar etiquetas en un sistema de juego.

#ifndef LABEL_H
#define LABEL_H

#include "juegobject.h"
#include <QString>

// Declaración adelantada de clases para evitar dependencias circulares.
class Nivel2;
class Cuadros;
class QPainter;

// Definición de la clase Label que hereda de JuegObject.
class Label : public JuegObject
{
public:
    // Constructor de la clase Label que toma un puntero al nivel como parámetro.
    Label(Nivel2* host);

    // Método que devuelve la firma de la etiqueta.
    QString signature();

    // Método que verifica si la etiqueta es visible.
    bool is_visible();

    // Método para generar una nueva etiqueta en las coordenadas dadas.
    void spawn(int x, int y);

    // Método para realizar acciones relacionadas con la etiqueta en el juego.
    void act();

    // Método para manejar la muerte de la etiqueta.
    void die();

    // Método que devuelve el valor de la etiqueta.
    int value();

    // Método para establecer la geometría de la etiqueta (ancho y alto).
    void set_geometry(int width, int height);

    // Método para establecer el texto de la etiqueta.
    void set_text(QString text);

    // Método para establecer el valor de la etiqueta.
    void set_value(int value);

    // Métodos que devuelven la posición, ancho, altura de la etiqueta.
    int x();
    int width();
    int y();
    int height();

    // Método para dibujar la etiqueta en un QPainter proporcionado.
    void draw(QPainter* painter);

private:
    Nivel2* _host;  // Puntero al nivel al que pertenece la etiqueta.
    Cuadros* _cuadros;    // Puntero a la cuadrícula del nivel.

    int _width_px = 1;    // Ancho de la etiqueta en píxeles.
    int _height_px = 1;   // Alto de la etiqueta en píxeles.
    bool _is_visible = false;  // Estado de visibilidad de la etiqueta.
    int _x;  // Posición x de la etiqueta.
    int _y;  // Posición y de la etiqueta.

    QString _text = "";  // Texto de la etiqueta.
    int _value = 0;      // Valor numérico de la etiqueta.
};

#endif // LABEL_H

