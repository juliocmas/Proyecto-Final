#include "item.h"

Item::Item(QString imagePath, int r, int c)
{
    // crear Pixmap con imagePath suministrado
    QPixmap image(imagePath);
    // escalar la imagen para corregir las dimensiones
    image = image.scaled(50,50);
    // establecer Pixmap en QObject
    setPixmap(image);

    // inicializar fila y columna
    row = r;
    col = c;

    // posición de ajuste
    setPosition(row, col);

}

void Item::setPosition(int r, int c)
{
    row = r;
    col = c;
    setPos(50 + (col * 50), (row* 50));
}
