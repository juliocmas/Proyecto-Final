#include "map.h"
#include <QString>
#include <QDebug>
#include <iostream>
#include <QFile>
#include <QTextStream>

const int INF = 99999;

// Constructor de la clase Map
Map::Map(int **boardData)
{
    // Inicializar la matriz 2D a ceros
    for(int i=0; i<122; i++)
        for(int j=0; j<122; j++)
            matrix[i][j] = 0;

    // Poblar la matriz de adyacencia con bordes
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (boardData[i][j] >= 0)
            {
                // Comprobar si el nodo superior no es una pared
                if (boardData[i-1][j] >= 0)
                {
                    matrix[boardData[i][j]][boardData[i - 1][j]] = 1;
                }

                // Comprobar si el nodo inferior no es una pared
                if (boardData[i+1][j] >= 0)
                {
                    matrix[boardData[i][j]][boardData[i + 1][j]] = 1;
                }

                // Comprobar si el nodo izquierdo no es una pared
                if (boardData[i][j-1] >= 0)
                {
                    matrix[boardData[i][j]][boardData[i][j-1]] = 1;
                }

                // Comprobar si el nodo derecho no es una pared
                if (boardData[i][j+1] >= 0)
                {
                    matrix[boardData[i][j]][boardData[i][j+1]] = 1;
                }
            }
        }
    }

    // Escribir la matriz en un archivo
    QFile file("C:\\proyectos\\RickAndMorty\\GameResources");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // Se va a escribir texto en el archivo
        QTextStream stream(&file);
        for(int i=0; i<122; i++)
        {
            for(int j=0; j<122; j++)
                stream << QString::number(matrix[i][j]) + " ";
            stream << "\n\r";
        }
        file.close();
        qDebug() << "Escritura finalizada";
    }
}

// Método para calcular el camino más corto
QVector<int> Map::calculateShortestPath(int startVertex, int endVertex)
{
    QVector<int> path;
    if(endVertex < 0)
    {
        // Devolver un camino vacío para que los personajes permanezcan quietos
        return path;
    }
    bool done[122];
    int previous[122];
    double cost[122];

    double temp[122][122];
    for (int i = 0; i < 122; i++)
        for (int j = 0; j < 122; j++)
            if (matrix[i][j] == 0)
                temp[i][j] = INF;
            else
                temp[i][j] = matrix[i][j];

    for (int i = 0; i < 122; i++)
    {
        if (i == startVertex)
        {
            done[i] = true;
            previous[i] = -1;
            cost[i] = 0;
        }
        else
        {
            done[i] = false;
            previous[i] = startVertex;
            cost[i] = temp[startVertex][i];
        }
    }

    int count = 1;

    while (count < 122)
    {
        // ¿Qué vértice está hecho?
        // Vértice con el costo más bajo.
        double minimum = INF;
        int currentVertex;
        for (int i = 0; i < 122; i++)
        {
            if (done[i] == false && cost[i] < minimum)
            {
                minimum = cost[i];
                currentVertex = i;
            }
        }
        done[currentVertex] = true;
        //
        for (int i = 0; i < 122; i++)
        {
            if (done[i] == false)
            {
                double value = cost[currentVertex] + temp[currentVertex][i];
                if (value < cost[i])
                {
                    cost[i] = value;
                    previous[i] = currentVertex;
                }
            }
        }
        count++;
    }
    int j;
    path.push_back(endVertex);
    j = endVertex;// para devolver solo el camino que nos interesaba
    while (j != startVertex)
    {
        path.insert(path.begin(), previous[j]);
        j = previous[j];
    }
    path.removeAt(0);
    return path;
}
