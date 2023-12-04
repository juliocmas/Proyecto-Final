#include "finaljuego.h"
#include "ui_finaljuego.h"
#include "nivel2.h"

FinalJuego::FinalJuego(bool win, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FinalJuego)
{
    // Configuración de la interfaz de usuario
    ui->setupUi(this);

    // Establecer el directorio actual para cargar recursos
    QDir::setCurrent("C:\\proyectos\\RickAndMorty\\GameResources");

    // Configuración del fondo de la ventana según si ganó o perdió
    QPixmap background;
    if(win)
    {
        setWindowTitle("Felicidades Rick Prime! Tienes tus Pistolas!");
        background =  QPixmap("winScreen.jpg");
    }
    else
    {
        setWindowTitle("Perdiste Ricky Prime!");
        background = QPixmap("loseScreen.jpg");
    }

    // Escalar el fondo para que se ajuste al tamaño de la ventana
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);

    // Configurar la paleta de colores de la ventana con el fondo escalado
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);
}

FinalJuego::~FinalJuego()
{
    // Liberar la memoria ocupada por la interfaz de usuario
    delete ui;
}

void FinalJuego::on_playAgainButton_clicked()
{
    // Crear una nueva instancia de InicioJuego y mostrarla
    InicioJuego* screen = new InicioJuego();
    screen->show();
    // Ocultar la ventana actual
    hide();
}

void FinalJuego::on_leaderBoardButton_clicked()
{
    // Crear una nueva instancia de TablaGamers y mostrarla
    MainWindow* screen = new MainWindow();
    screen->show();
}
