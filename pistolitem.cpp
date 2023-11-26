#include "pistolitem.h"

PistolItem::PistolItem(int r, int c): Item("pistol.png", r, c)
{
    collected = false;
}

void PistolItem::setCollected(bool b)
{
    collected = b;
}

bool PistolItem::isCollected()
{
    return collected;
}

void PistolItem::setId(int i)
{
    id = i;
}

int PistolItem::getId()
{
    return id;
}
