#include "caracter.h"

Caracter::Caracter(QString imagePath, int** boardData, int r, int c)
{
    // crea Pixmap con imagePath suministrado
    QPixmap image(imagePath);
    // escalar la imagen para corregir las dimensiones
    image = image.scaled(50,50);
    // establecer Pixmap en QObject
    setPixmap(image);

    // inicializar fila y columna
    row = r;
    col = c;

    // establezca la dirección en 1 ya que inicialmente el objeto mirará hacia la derecha
    direction = 1;

    // set the position of the QObject in the board
    setPosition(row, col);

    // initalize 2D data array
    data = new int*[16];
    for(int i=0; i<16; i++)
        *(data+i) = new int[16];

    // copiar datos de la matriz 2D boardData suministrada a la matriz de datos
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<16; j++)
        {
            *(*(data+i)+j) = *(*(boardData+i)+j);
        }
    }

}

void Caracter::setDirection(int d)
{
    direction = d;
    QTransform transform;

    // comprobar si el objeto mirará hacia la izquierda
    if(d == -1)
    {
        // voltear el objeto sobre el eje y
        transform.scale(-1,1);
        transform.translate(-50,0);
    }

    // transformar desde el QObject
    // Si el objeto mira hacia la derecha, se establecerá una transformación vacía, lo que
    //hará que el objeto no se transforme (volver a la orientación original).
    setTransform(transform);
}

void Caracter::setPosition(int r, int c)
{
    // actualizar variables de fila y columna
    row = r;
    col = c;

    //actualizar la posición del QObject
    setPos(50 + col*50, row*50);
}

void Caracter::updateImage(QString imagePath)
{
    // crear Pixmap con imagePath suministrado
    QPixmap temp(imagePath);
    // escalar la imagen para corregir las dimensiones
    temp = temp.scaled(50,50);
    // establecer Pixmap en QObject
    setPixmap(temp);
}

void Caracter::moveUp()
{
    // comprobar si el movimiento es válido
    if(validMovement(up))
        setPosition(row-1,col);
}
void Caracter::moveDown()
{
    // comprobar si el movimiento es válido
    if(validMovement(down))
        setPosition(row+1,col);
}

void Caracter::moveRight()
{
    // comprobar si el movimiento es válido
    if(validMovement(right))
    {
        // hacer que el personaje mire hacia la derecha
        setDirection(1);
        setPosition(row,col+1);
    }
}

void Caracter::moveLeft()
{
    // comprobar si el movimiento es válido
    if(validMovement(left))
    {
        // hacer que el personaje mire hacia la izquierda
        setDirection(-1);
        setPosition(row,col-1);
    }
}

int Caracter::getData()
{
    return *(*(data+row)+col);
}
int Caracter::getData(int r, int c)
{
    return *(*(data+r)+c);
}

void Caracter::getPosition(int current, int& row, int& col)
{
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<16; j++)
        {
            if(*(*(data+i)+j) == current)
            {
                row = i;
                col = j;
                return;
            }
        }
    }
    row = -1;
    col = -1;
}

