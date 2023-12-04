#include "juegoscreen.h"
#include <QDebug>

// Constructor de la clase JuegoScreen
JuegoScreen::JuegoScreen(int level, int ricks, User &account)
{
    // Configuración de la pantalla
    setFixedSize(810, 810);
    setWindowTitle("Rick and Morty");

    // Crear escena para el juego
    scene = new QGraphicsScene;
    currentUser = account;

    // Leer datos del archivo de tablero
    data = new int*[16];
    for(int i=0; i<16; i++)
        *(data+i) = new int[16];
    QDir::setCurrent("C:\\proyectos\\RickAndMorty\\GameResources");
    QFile file("map.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    QString temp;

    for(int i=0; i<16; i++)
    {
        for(int j=0; j<16; j++)
        {
            stream >> temp;
            *(*(data+i)+j) = temp.toInt();
        }
    }

    // Configurar transformaciones para su uso en rotaciones
    QTransform rotate90, rotate180, rotate270;
    rotate90.rotate(90);
    rotate180.rotate(180);
    rotate270.rotate(270);

    // Establecer imágenes para diferentes partes del tablero
    QPixmap boardImages[5] = {QPixmap("solidBorder.jpg"), QPixmap("horizontalBorder.jpg"), QPixmap("tCornerBorder.jpg"), QPixmap("edgeCornerBorder.jpg"), QPixmap("blackBackground.jpg")};
    // Escalar imágenes a las dimensiones correctas
    for(int i=0; i<5; i++)
        boardImages[i] = boardImages[i].scaled(50,50);

    // Agregar imágenes de fondo al tablero
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<16; j++)
        {
            QGraphicsPixmapItem* temp = new QGraphicsPixmapItem();

            switch(*(*(data+i)+j))
            {
            case -1: temp->setPixmap(boardImages[0]); break;
            case -2: temp->setPixmap(boardImages[1]); break;
            case -3: temp->setPixmap(boardImages[1].transformed(rotate90)); break;
            case -4: temp->setPixmap(boardImages[2].transformed(rotate90)); break;
            case -5: temp->setPixmap(boardImages[2].transformed(rotate270)); break;
            case -6: temp->setPixmap(boardImages[2]); break;
            case -7: temp->setPixmap(boardImages[2].transformed(rotate180)); break;
            case -8: temp->setPixmap(boardImages[3]); break;
            case -9: temp->setPixmap(boardImages[3].transformed(rotate90)); break;
            case -10: temp->setPixmap(boardImages[3].transformed(rotate180)); break;
            case -11: temp->setPixmap(boardImages[3].transformed(rotate270)); break;
            case -20: temp->setPixmap(boardImages[4]); break;
            default: temp->setPixmap(boardImages[4]); break;
            }

            temp->setPos(50 + (50*j), (50*i));
            scene->addItem(temp);
        }
    }

    // Crear personajes
    rickCounter = ricks;
    rick = new Rick*[rickCounter];
    for(int i = 0; i < rickCounter; i++)
    {
        *(rick+i) = new Rick(data, level, i);
        scene->addItem(*(rick+i));
    }
    prime = new Prime(data);

    // Poner el foco en Prime
    prime->setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    prime->setFocus();

    // Poner a Prime en la parte superior de todos los elementos
    prime->setZValue(1);

    // Crear Poder del Portal
    powerUps[0] = new PowerUp(5,5);
    powerUps[1] = new PowerUp(10,10);

    // Crear pistolas
    pistols[0] = new PistolItem(1,1);
    pistols[1] = new PistolItem(14,14);
    pistols[2] = new PistolItem(1,14);
    pistols[3] = new PistolItem(14,1);

    // Crear etiquetas
    HealthLabel = new ContadorInicio("Vidas: ", 3, 500, 0);
    PistolLabel = new ContadorInicio("Pistolas: ", 4, 300, 0);

    // Agregar objetos a la escena
    scene->addItem(prime);
    scene->addItem(powerUps[0]);
    scene->addItem(powerUps[1]);
    scene->addItem(pistols[0]);
    scene->addItem(pistols[1]);
    scene->addItem(pistols[2]);
    scene->addItem(pistols[3]);
    scene->addItem(HealthLabel);
    scene->addItem(PistolLabel);

    // Conectar señales y slots
    // Slots para los contadores de las etiquetas
    connect(prime, SIGNAL(decreaseHealthCounter()), HealthLabel, SLOT(decreaseCounter()));
    connect(prime, SIGNAL(decreasePistolCounter()), PistolLabel, SLOT(decreaseCounter()));
    // Slots para el cambio de movimiento de Prime
    for(int i = 0; i < rickCounter; i++)
    {
        connect(prime, SIGNAL(changeMotion()), (*(rick+i)), SLOT(changeTarget()));
    }
    // Slots para el cambio de estado del juego
    connect(prime, SIGNAL(endGame()), this, SLOT(gameOver()));
    connect(prime, SIGNAL(winGame()), this, SLOT(win()));

    for(int i = 0; i < rickCounter; i++)
    {
        (*(rick+i))->startMovement();
    }
    setScene(scene);
    gameTimer.start();
}

void JuegoScreen::win()
{
    // Implementa lo que sucede cuando se gana el juego
    qDebug() << "¡Has ganado!";
    // Puedes agregar más lógica aquí según tus necesidades
}



// Slot para el fin del juego
void JuegoScreen::gameOver()
{
    for(int i = 0; i < rickCounter; i++)
    {
        (*(rick+i))->stopMovement();
    }
    FinalJuego* screen = new FinalJuego(false);
    screen->show();
    hide();
}


