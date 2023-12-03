#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "engine.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);  // Constructor de la clase
    ~MainWindow();  // Destructor de la clase

    // Funciones que devuelven variables globales (para objetos externos)
    int SCREEN_WIDTH_PX();
    int SCREEN_HEIGHT_PX();

    // Funciones de dibujo y manejo de eventos de teclado
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent* event);

public slots:
    void update_game();  // Función para actualizar el juego

private:
    Ui::MainWindow *ui;  // Interfaz de usuario

    // Variables globales
    int _SCREEN_WIDTH_PX = 800;
    int _SCREEN_HEIGHT_PX = 600;
    int _UPDATE_DELAY_MS = 40;
    Engine engine = Engine(_SCREEN_WIDTH_PX, _SCREEN_HEIGHT_PX);  // Instancia del motor del juego
};
#endif // MAINWINDOW_H
