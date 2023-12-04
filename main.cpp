#include "iniciojuego.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InicioJuego w;

    //Utilizando los métodos SCREEN_WIDTH_PX y SCREEN_HEIGHT_PX
    w.setFixedSize(w.SCREEN_WIDTH_PX(), w.SCREEN_HEIGHT_PX());
    w.setWindowTitle("Rick and Morty");

    w.show();
    return a.exec();
}
