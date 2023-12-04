#ifndef JUEGOBJECT_H
#define JUEGOBJECT_H

class QString;
class QPainter;

class JuegObject
{
public:
    JuegObject();

    virtual void act();
    virtual void spawn(int x, int y);
    virtual void die();
    virtual void draw(QPainter* painter);

    virtual int x();
    virtual int width();
    virtual int y();
    virtual int height();
    virtual QString signature();
    virtual bool is_visible();

    virtual ~JuegObject();
};

#endif // JUEGOBJECT_H
