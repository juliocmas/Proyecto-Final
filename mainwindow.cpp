#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QImage>
#include <QString>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Configuración de la conexión del temporizador para la actualización del juego
    QTimer* timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(update_game()));
    timer->start(_UPDATE_DELAY_MS);  // Inicia el temporizador con el intervalo definido
}

MainWindow::~MainWindow()
{
    delete ui;  // Libera la memoria ocupada por la interfaz de usuario
}

int MainWindow::SCREEN_WIDTH_PX()
{
    return this->_SCREEN_WIDTH_PX;  // Devuelve el ancho de la pantalla en píxeles
}

int MainWindow::SCREEN_HEIGHT_PX()
{
    return this->_SCREEN_HEIGHT_PX;  // Devuelve la altura de la pantalla en píxeles
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    engine.draw_game(&painter);  // Llama al método para dibujar el juego en el objeto QPainter
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // Manejo de eventos de teclado para las teclas Espacio, Izquierda y Derecha
    if (event->key() == Qt::Key_Space) {
        engine.try_update_keyboard_state("space", true);
    } else if (event->key() == Qt::Key_Left) {
        engine.try_update_keyboard_state("left", true);
    } else if (event->key() == Qt::Key_Right) {
        engine.try_update_keyboard_state("right", true);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    // Manejo de eventos de liberación de teclas para las teclas Espacio, Izquierda y Derecha
    if (event->key() == Qt::Key_Space) {
        engine.try_update_keyboard_state("space", false);
    } else if (event->key() == Qt::Key_Left) {
        engine.try_update_keyboard_state("left", false);
    } else if (event->key() == Qt::Key_Right) {
        engine.try_update_keyboard_state("right", false);
    }
}

void MainWindow::update_game()
{
    engine.init_turn();  // Inicia un nuevo turno del juego
    repaint();  // Vuelve a pintar la interfaz gráfica

    // Comprueba si el juego ha terminado o si se ha alcanzado la victoria
    if (engine.is_game_over()) {
        QMessageBox msgbox;
        msgbox.setText("Game Over!");
        msgbox.exec();
        qApp->quit();  // Cierra la aplicación
    } else if (engine.is_victory()) {
        QMessageBox msgbox;
        msgbox.setText("VICTORY!!!");
        msgbox.exec();
        qApp->quit();  // Cierra la aplicación
    }
}

