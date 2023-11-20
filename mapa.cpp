#include "map.h"
#include <QString>
#include <QDebug>
#include <iostream>
#include <QFile>
#include <QTextStream>

const int INF = 99999;

Map::Map(int **boardData)
{
    
    for(int i=0; i<122; i++)
        for(int j=0; j<122; j++)
            matrix[i][j] = 0;

    // Llena la matriz de adyacencia con aristas
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (boardData[i][j] >= 0)
            {
                // comprobar si nodo superior no es una pared
                if (boardData[i-1][j] >= 0)
                {
                    matrix[boardData[i][j]][boardData[i - 1][j]] = 1;
                }

                // Compruebe  nodo inferior no es una pared
                if (boardData[i+1][j] >= 0)
                {
                    matrix[boardData[i][j]][boardData[i + 1][j]] = 1;
                }

                // Comprobar si nodo izquierdo no es una pared
                if (boardData[i][j-1] >= 0)
                {
                    matrix[boardData[i][j]][boardData[i][j-1]] = 1;
                }

                // comprobar si nodo derecho no es una pared
                if (boardData[i][j+1] >= 0)
                {
                    matrix[boardData[i][j]][boardData[i][j+1]] = 1;
                }
            }
        }
    }


    QFile file("C:\\proyectos\\RickAndMorty\\GameResources");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      // vamos a transmitir texto al archivo
      QTextStream stream(&file);
      for(int i=0; i<122; i++)
      {
          for(int j=0; j<122; j++)
              stream << QString::number(matrix[i][j]) + " ";
          stream << "\n\r";
      }
      file.close();
      qDebug() << "Writing finished";
    }

}

QVector<int> Map::calculateShortestPath(int startVertex, int endVertex)
{
    QVector<int> path;
    if(endVertex < 0)
    {
        // Regresar al camino vacío ya que los personajes se queden fijos
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
        // ¿Qué vértice se esta usando?
        // Vértice con el menor costo.
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
    j = endVertex;// regresar solo por el camino que nos interesa
    while (j != startVertex)
    {
        path.insert(path.begin(), previous[j]);
        j = previous[j];
    }
    path.removeAt(0);
    return path;
}
