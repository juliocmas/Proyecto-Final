#include "user.h"

// Constructor predeterminado de la clase User
User::User()
{}

// Constructor de la clase User que inicializa el nombre de usuario y el tiempo
User::User(QString name, int t)
{
    username = name;
    time = t;
}

// Método para obtener el nombre de usuario
QString User::getUsername()
{
    return username;
}

// Método para establecer el nombre de usuario
void User::setUsername(QString name)
{
    username = name;
}

// Método para establecer el tiempo
void User::setTime(int t)
{
    time = t;
}

// Método para obtener el tiempo
int User::getTime()
{
    return time;
}

// Sobrecarga del operador menor que para comparar usuarios por tiempo
bool User::operator<(User &rhs)
{
    return this->time < rhs.time;
}

// Sobrecarga del operador mayor que para comparar usuarios por tiempo
bool User::operator>(User &rhs)
{
    return this->time > rhs.time;
}
