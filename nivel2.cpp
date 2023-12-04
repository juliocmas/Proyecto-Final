#include "nivel2.h"
#include "cuadros.h"
#include "juegobject.h"
#include "nave.h"
#include "nespacial.h"
#include "disparo.h"
#include "bomba.h"
#include "label.h"
#include <QPainter>
#include <ctime>

Nivel2::Nivel2()
    : Nivel2(800, 600) {}

Nivel2::Nivel2(int gamefield_width, int gamefield_height)
{
    _gamefield_width = gamefield_width;
    _gamefield_height = gamefield_height;
    _cuadros = new Cuadros(gamefield_width / 5, gamefield_height / 5);

    _keyboard_state["space"] = false;
    _keyboard_state["left"] = false;
    _keyboard_state["right"] = false;

    this->init_game();
}

// Rest of the code...


Cuadros* Nivel2::cuadros()
{
    return _cuadros;
}

void Nivel2::init_game()
{
    std::srand(std::time(nullptr));

    _label_life_count = new Label(this);
    _label_life_count->set_text("VIDAS");
    _label_life_count->set_geometry(_gamefield_width / 2, 50);
    _label_life_count->set_value(5);
    this->add_object(_label_life_count);
    _label_life_count->spawn(0, 0);

    _label_score_count = new Label(this);
    _label_score_count->set_text("     PUNTOS");
    _label_score_count->set_geometry(_gamefield_width / 2, 50);
    _label_score_count->set_value(0);
    this->add_object(_label_score_count);
    _label_score_count->spawn(_gamefield_width / 2, 0);

    Label* label_floor = new Label(this);
    label_floor->set_geometry(_gamefield_width, 20);
    this->add_object(label_floor);
    label_floor->spawn(0, _gamefield_height - 20);

    Nespacial* nespacial = new Nespacial(this);
    this->add_object(nespacial);
    nespacial->spawn(_gamefield_width / 2 - nespacial->width() / 2, _gamefield_height - 30 - nespacial->height());
}

void Nivel2::init_turn()
{
    int naves_count = 0;
    for (int i = 0; i < _objects.size(); ++i) {
        if (_objects[i]->signature() == "Nave") {
            ++naves_count;
        }
    }
    if (naves_count == 0) {
        if (_naves_rows == 4) {
            this->victory();
        }
        else {
            this->spawn_naves(_naves_per_row, _naves_rows);
            _naves_count = _naves_per_row * _naves_rows;
            ++_naves_rows;
        }
    }

    for (int i = 0; i < _objects.size(); ++i) {
        _objects[i]->act();
        for (int j = 0; j < _messages.size(); ++j) {
            this->process_message(_messages[j]);
        }
        _messages.clear();
    }
}

void Nivel2::draw_game(QPainter* painter)
{
    for (int i = 0; i < _objects.size(); ++i) {
        _objects[i]->draw(painter);
    }
}

void Nivel2::recieve_message(QString event_name, QVector<JuegObject *> affected_entities)
{
    Message new_message;
    new_message.event_name = event_name;
    new_message.affected_entities = affected_entities;
    _messages.append(new_message);
}

void Nivel2::process_message(Message message)
{
    if (message.event_name == "shoot") {
        JuegObject* shooter = message.affected_entities[0];
        if (shooter->signature() == "nespacial") {
            Disparo* disparo = new Disparo(this);
            int xpos = shooter->x() + shooter->width() / 2 - disparo->width() / 2;
            int ypos = shooter->y() - disparo->height() - 20;
            disparo->spawn(xpos, ypos);
            if (disparo->is_visible()) {
                this->add_object(disparo);
            }
            else {
                delete disparo;
            }
        }
        else if (shooter->signature() == "Nave") {
            Bomba* bomba = new Bomba(this);
            int xpos = shooter->x() + shooter->width() / 2 - bomba->width() / 2;
            int ypos = shooter->y() + shooter->height() + 20;
            bomba->spawn(xpos, ypos);
            if (bomba->is_visible()) {
                this->add_object(bomba);
            }
            else {
                delete bomba;
            }
        }
    }
    else if (message.event_name == "collision") {
        JuegObject* obj1 = message.affected_entities[0];
        JuegObject* obj2 = message.affected_entities[1];
        if ((obj1->signature() == "Nave" && obj2->signature() == "Disparo")
            ||  (obj1->signature() == "Disparo" && obj2->signature() == "Nave")) {
            this->delete_object(obj1);
            this->delete_object(obj2);
            --_naves_count;
            _score += 500;
            _label_score_count->set_value(_score);
        }
        else if (obj1->signature() == "Bomba" && obj2->signature() == "Disparo") {
            this->delete_object(obj2);
        }
        else if (obj1->signature() == "Disparo" && obj2->signature() == "Bomba") {
            this->delete_object(obj1);
        }
        else if (obj1->signature() == "Bomba" && obj2->signature() == "Nespacial") {
            this->delete_object(obj1);
            this->game_over();
        }
        else if (obj1->signature() == "Nespacial" && obj2->signature() == "Bomba") {
            this->delete_object(obj2);
            this->game_over();
        }
        else if (obj1->signature() == "Nave" && obj2->signature() == "Nespacial") {
            this->delete_object(obj1);
            this->game_over();
            --_naves_count;
            _score += 500;
            _label_score_count->set_value(_score);
        }
        else if (obj1->signature() == "Nespacial" && obj2->signature() == "nave") {
            this->delete_object(obj2);
            this->game_over();
            --_naves_count;
            _score += 500;
            _label_score_count->set_value(_score);
        }

        else if (obj1->signature() == "Bomba" && obj2->signature() == "Label") {
            this->delete_object(obj1);
        }
        else if (obj1->signature() == "Disparo" && obj2->signature() == "Label") {
            this->delete_object(obj1);
        }
        else if (obj1->signature() == "nave" && obj2->signature() == "Label") {
            this->game_over();
        }

        else if (obj1->signature() == "Bomba" && obj2->signature() == "Bomba") {
            this->delete_object(obj1);
            this->delete_object(obj2);
        }
        else if (obj1->signature() == "Nave" && obj2->signature() == "Bomba") {
            this->delete_object(obj2);
        }
        else if (obj1->signature() == "Bomba" && obj2->signature() == "Nave") {
            this->delete_object(obj1);
        }
    }
}

void Nivel2::add_object(JuegObject *object)
{
    _objects.append(object);
}

void Nivel2::delete_object(JuegObject *object)
{
    object->die();
    for (int i = 0; i < _objects.size(); ++i) {
        if (_objects[i] == object) {
            _objects.removeAt(i);
            break;
        }
    }
    delete object;
}

void Nivel2::try_update_keyboard_state(QString key_name, bool new_state)
{
    if (key_name == "space") {
        _keyboard_state["space"] = new_state;
    }
    else if (key_name == "left") {
        if (new_state == true) {
            if (_keyboard_state["right"] == false) {
                _keyboard_state["left"] = true;
            }
        }
        else {
            _keyboard_state["left"] = false;
        }
    }
    else if (key_name == "right") {
        if (new_state == true) {
            if (_keyboard_state["left"] == false) {
                _keyboard_state["right"] = true;
            }
        }
        else {
            _keyboard_state["right"] = false;
        }
    }
}

bool Nivel2::keyboard_state(QString key_name)
{
    return _keyboard_state[key_name];
}

void Nivel2::spawn_naves(int naves_per_row, int rows)
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < naves_per_row; ++j) {
            Nave* nave = new Nave(this);
            if (i == rows - 1) {
                nave->give_ammo();
            }
            nave->spawn(45 + j*(nave->width() + 40), 55 + i*(nave->height() + 30));
            if (nave->is_visible()) {
                this->add_object(nave);
            }
            else {
                delete nave;
            }
        }
    }
}

void Nivel2::victory()
{
    _is_victory = true;
}

void Nivel2::game_over()
{
    if (_life_count > 0) {
        --_life_count;
        _label_life_count->set_value(_life_count);
    }
    else {
        _is_game_over = true;
    }
}

bool Nivel2::is_victory()
{
    return _is_victory;
}

bool Nivel2::is_game_over()
{
    return _is_game_over;
}

Nivel2::~Nivel2()
{
    delete _cuadros;
}

