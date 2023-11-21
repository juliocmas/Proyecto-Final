#include "iniciojuego.h"
#include "ui_iniciojuego.h"

// Constructor de la clase InicioJuego
InicioJuego::InicioJuego(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InicioJuego)
{
    // Configuración de la interfaz de usuario
    ui->setupUi(this);

    // Establecer el directorio actual para cargar recursos
    QDir::setCurrent("C:\\proyectos\\RickAndMorty\\GameResources");

    // Cargar una imagen de fondo y escalarla para que se ajuste al tamaño de la ventana
    QPixmap background("welcomeScreen.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);

    // Configurar la paleta de colores de la ventana con el fondo escalado
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);
}

// Destructor de la clase InicioJuego
InicioJuego::~InicioJuego()
{
    // Liberar la memoria ocupada por la interfaz de usuario
    delete ui;
}

// Manejador de eventos para el botón "playButton"
void InicioJuego::on_playButton_clicked()
{
    // Verificar si el campo de nombre no está vacío
    if (!ui->nameText->text().isEmpty())
    {
        // Crear una instancia de la clase User y establecer el nombre
        User account;
        account.setUsername(ui->nameText->text());

        // Crear una instancia de JuegoScreen con los parámetros especificados y mostrarla
        JuegoScreen* screen = new JuegoScreen(ui->difficulty->currentIndex(), ui->spinBox->value(), account);
        screen->show();

        // Ocultar la ventana actual
        hide();
    }
    else
    {
        // Mostrar un mensaje de error si el campo de nombre está vacío
        QMessageBox msgBox;
        msgBox.setText("ERROR: Ingrese usuario, ¡No deje el espacio vacío!");
        msgBox.exec();
    }
}
