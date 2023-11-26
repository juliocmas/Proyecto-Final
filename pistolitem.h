#ifndef PISTOLITEM_H
#define PISTOLITEM_H

#include "item.h"

class PistolItem: public Item
{
public:
    PistolItem(int r, int c);
    void setCollected(bool b);
    bool isCollected();
    void setId(int i);
    int getId();
private:
    bool collected;
    int id;
};

#endif // PISTOLITEM_H
