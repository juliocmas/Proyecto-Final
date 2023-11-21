#include "contadorinicio.h"

ContadorInicio::ContadorInicio(QString l, int c, int x, int y)
{
    // Personacion de Fuentes
    QFont font;
    font.setBold(true);
    font.setPixelSize(20);
    setDefaultTextColor(Qt::white);
    setFont(font);

    // posiciónamiento
    setPos(x,y);

    // Inicializar valor contador
    counter = c;

    // establecer etiqueta de texto
    label = l;

    //  texto de etiqueta
    setPlainText(label + QString::number(counter));
}

void ContadorInicio::decreaseCounter()
{
    // Contador Decreciente
    counter--;

    // actualizador el texto en etiqueta
    setPlainText(label + QString::number(counter));
}
