#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QVector>
#include <QPixmap>
#include <QFile>
#include <QDir>
#include "user.h"
#include "nivel2.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor de la clase MainWindow
    explicit MainWindow(QWidget *parent = nullptr);

    // Destructor de la clase MainWindow
    ~MainWindow();

private slots:
    // Slot para manejar el evento de hacer clic en el botón de cerrar
    void on_closeButton_clicked();

    // Métodos para obtener las dimensiones de la pantalla
    int SCREEN_WIDTH_PX();
    int SCREEN_HEIGHT_PX();

    // Métodos para manejar eventos de pintura y teclado
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent* event);

public slots:
    // Slot para actualizar el juego en intervalos regulares
    void update_game();

private:
    Ui::MainWindow *ui;  // Interfaz de usuario de la ventana

    // Dimensiones de la pantalla y frecuencia de actualización del juego
    int _SCREEN_WIDTH_PX = 800;
    int _SCREEN_HEIGHT_PX = 600;
    int _UPDATE_DELAY_MS = 40;

    // Instancia del motor del juego
    Nivel2 nivel2 = Nivel2(_SCREEN_WIDTH_PX, _SCREEN_HEIGHT_PX);
};

#endif // MAINWINDOW_H
