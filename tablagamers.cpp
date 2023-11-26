#include "tablagamers.h"
#include "ui_tablagamers.h"

// Constructor de la clase TablaGamers
TablaGamers::TablaGamers(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TablaGamers)
{
    // Configurar el directorio de trabajo y el fondo de la ventana
    QDir::setCurrent("C:\\proyectos\\RickAndMorty\\GameResources");
    QPixmap background("blackBackground.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);

    // Inicializar el vector de usuarios
    QVector<User> users;
    ui->setupUi(this);

    // Leer datos de usuarios desde el archivo
    QFile file("C:\\proyectos\\RickAndMorty\\GameResources");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    // Procesar cada línea del archivo y almacenarla en el vector de usuarios
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList userData = line.split(" ");
        users.push_back(User(userData[0], userData[1].toInt()));
    }

    // Ordenar el vector de usuarios por tiempo utilizando el algoritmo de merge sort
    mergeSort(users, 0, users.size()-1);

    // Actualizar el archivo con los usuarios ordenados y mostrarlos en la lista
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&file);
    for(QVector<User>::iterator i=users.begin(); i!=users.end(); i++)
    {
        QString line = i->getUsername() + " " + QString::number(i->getTime());
        ui->listWidget->addItem(line);
        stream << line << "\n";
    }
    file.close();
}

// Método para agregar un usuario al archivo
void TablaGamers::addUser(User &account)
{
    int index = findUser(account);
    if(index == -1)
    {
        QFile file("C:\\proyectos\\RickAndMorty\\GameResources");
        if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        {
            // Escribir el nuevo usuario en el archivo
            QTextStream stream(&file);
            stream << account.getUsername() << " " << account.getTime() << "\n";
            file.close();
        }
    } else {
        updateUser(index, account.getTime());
    }
}

// Método para buscar un usuario en el archivo y devolver su índice
int TablaGamers::findUser(User &account)
{
    QFile file("C:\\proyectos\\RickAndMorty\\GameResources");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    int index = 0;
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList userData = line.split(" ");
        if(userData[0] == account.getUsername())
            return index;
        index++;
    }
    return -1;
}

// Método para actualizar el tiempo de un usuario existente en el archivo
void TablaGamers::updateUser(int index, int time)
{
    QFile file("C:\\proyectos\\RickAndMorty\\GameResources");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);
    QString output;
    int i = 0;
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList userData = line.split(" ");
        if(i==index)
        {
            output += userData[0] + " "  + QString::number(time) + "\n";
        } else {
            output += line + "\n";
        }
        i++;
    }
    file.close();

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // Escribir la salida actualizada en el archivo
        QTextStream stream(&file);
        stream << output;
        file.close();
    }
}

// Método para realizar el algoritmo de merge sort en un vector de usuarios
void TablaGamers::mergeSort(QVector<User> &vec, int start, int end)
{
    if(start<end)
    {
        int middle = (start+end)/2;
        mergeSort(vec, start,middle);
        mergeSort(vec, middle+1,end);
        merge(vec, start,middle,end);
    }
}

// Método para realizar la operación de fusión en el algoritmo de merge sort
void TablaGamers::merge(QVector<User> &vec, int start, int middle, int end)
{
    int i = start;
    int j = middle+1;
    QVector<User> temp;

    while(i<=middle && j<=end)
    {
        if(vec[i]<vec[j])
        {
            temp.push_back(vec.at(i));
            i++;
        } else {
            temp.push_back(vec.at(j));
            j++;
        }
    }

    while(i<=middle)
    {
        temp.push_back(vec.at(i));
        i++;
    }

    while(j<=end)
    {
        temp.push_back(vec.at(j));
        j++;
    }

    int k = 0;
    for(QVector<User>::Iterator i = vec.begin()+start; i !=vec.begin()+end+1; i++)
    {
        *i = temp.at(k);
        k++;
    }
}

// Destructor de la clase TablaGamers
TablaGamers::~TablaGamers()
{
    delete ui;
}

// Método para manejar el evento de hacer clic en el botón de cerrar
void TablaGamers::on_closeButton_clicked()
{
    hide();
}
