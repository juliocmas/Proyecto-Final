#include "iniciojuego.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InicioJuego w;
    w.show();
    return a.exec();
}
