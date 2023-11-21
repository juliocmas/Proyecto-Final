#ifndef CONTADORINICIO_H
#define CONTADORINICIO_H

#include <QGraphicsTextItem>
#include <QFont>
#include <QString>

class ContadorInicio: public QGraphicsTextItem
{
    Q_OBJECT
public:
    ContadorInicio(QString l, int c, int x, int y);
public slots:
    void decreaseCounter();
private:
    QString label;
    int counter;
};

#endif // CONTADORINICIO_H
