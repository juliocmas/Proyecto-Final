#ifndef CUADROS_H
#define CUADROS_H

#include <QVector>
class JuegObject;

class Cuadros
{
public:
    Cuadros();
    Cuadros(int width, int height);

    bool is_free(int x, int y);
    bool is_owned(int x, int y);
    JuegObject* owner(int x, int y);
    void own(int x, int y, JuegObject* object);
    void free(int x, int y);

    int width();
    int height();

private:
    int _width;
    int _height;
    QVector <QVector <JuegObject*> > _data;
};

#endif // CUADROS_H
