// Archivo: nivel2.h
// Definición de la clase Nivel2 para representar el nivel de juego y sus elementos.

#ifndef NIVEL2_H
#define NIVEL2_H

#include <QVector>
#include <QString>
#include <QMap>
#include "cuadros.h"
class JuegObject;
class QPainter;
class Label;

class Nivel2
{
public:
    // Estructura para representar mensajes del juego.
    struct Message
    {
        QString event_name; // "colisión", "disparo"
        QVector<JuegObject*> affected_entities;
    };

    // Constructor predeterminado de la clase Nivel2.
    Nivel2();

    // Constructor de la clase Nivel2 que toma el ancho y alto del campo de juego como parámetros.
    Nivel2(int gamefield_width, int gamefield_height);

    // Método que devuelve el puntero a la cuadrícula del nivel.
    Cuadros* cuadros();

    // Métodos para inicializar el juego y el turno.
    void init_game();
    void init_turn();

    // Método para dibujar el estado del juego utilizando un QPainter proporcionado.
    void draw_game(QPainter* painter);

    // Método para recibir mensajes del juego.
    void recieve_message(QString event_name, QVector<JuegObject*> affected_entities);

    // Método para procesar un mensaje específico del juego.
    void process_message(Message message);

    // Métodos para agregar y eliminar objetos del juego.
    void add_object(JuegObject* object);
    void delete_object(JuegObject* object);

    // Métodos para intentar actualizar el estado del teclado y consultar su estado actual.
    void try_update_keyboard_state(QString key_name, bool new_state); // "izquierda", "derecha", "espacio"
    bool keyboard_state(QString key_name);

    // Métodos relacionados con la victoria y el fin del juego.
    void spawn_naves(int naves_per_row, int rows);
    void victory();
    void game_over();
    bool is_victory();
    bool is_game_over();

    // Destructor de la clase Nivel2.
    ~Nivel2();

private:
    int _gamefield_width;        // Ancho del campo de juego.
    int _gamefield_height;       // Alto del campo de juego.
    Cuadros* _cuadros;                 // Puntero a la cuadrícula del nivel.
    QVector<JuegObject*> _objects; // Vector de punteros a objetos del juego.
    QVector<Message> _messages;    // Vector de mensajes del juego.
    QMap<QString, bool> _keyboard_state; // Mapa que almacena el estado del teclado.

    int _life_count = 5;           // Contador de vidas del jugador.
    int _score = 0;                // Puntuación del jugador.
    int _naves_per_row = 6;        // Número de naves por fila.
    int _naves_count = 0;          // Contador de naves.
    int _naves_rows = 1;           // Número de filas de naves.

    Label* _label_life_count;      // Etiqueta para mostrar el contador de vidas.
    Label* _label_score_count;     // Etiqueta para mostrar la puntuación.
    bool _is_game_over = false;    // Indicador de fin de juego.
    bool _is_victory = false;      // Indicador de victoria.
};

#endif // NIVEL2_H


