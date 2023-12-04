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

    // Conectar ranuras
    QTimer* timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(update_game()));
    timer->start(_UPDATE_DELAY_MS);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::SCREEN_WIDTH_PX()
{
    return this->_SCREEN_WIDTH_PX;
}

int MainWindow::SCREEN_HEIGHT_PX()
{
    return this->_SCREEN_HEIGHT_PX;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    nivel2.draw_game(&painter);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space) {
        nivel2.try_update_keyboard_state("space", true);
    }
    else if (event->key() == Qt::Key_Left) {
        nivel2.try_update_keyboard_state("left", true);
    }
    else if (event->key() == Qt::Key_Right) {
        nivel2.try_update_keyboard_state("right", true);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space) {
        nivel2.try_update_keyboard_state("space", false);
    }
    else if (event->key() == Qt::Key_Left) {
        nivel2.try_update_keyboard_state("left", false);
    }
    else if (event->key() == Qt::Key_Right) {
        nivel2.try_update_keyboard_state("right", false);
    }
}

void MainWindow::update_game()
{
    nivel2.init_turn();
    repaint();

    if (nivel2.is_game_over()) {
        QMessageBox msgbox;
        msgbox.setText("GAME OVER!");
        msgbox.exec();
        qApp->quit();
    }
    else if (nivel2.is_victory()) {
        QMessageBox msgbox;
        msgbox.setText("GANASTE!!!");
        msgbox.exec();
        qApp->quit();
    }
}

// Método para manejar el evento de hacer clic en el botón de cerrar
void MainWindow::on_closeButton_clicked()
{
    hide();
}
