#ifndef INICIOJUEGO_H
#define INICIOJUEGO_H

#include <QMainWindow>
#include <QPixmap>
#include <QDir>
#include <QMessageBox>
#include <juegoscreen.h>
#include "nivel2.h"



QT_BEGIN_NAMESPACE
namespace Ui { class InicioJuego; }
QT_END_NAMESPACE


class InicioJuego : public QMainWindow
{
    Q_OBJECT

public:

    int SCREEN_WIDTH_PX();
    int SCREEN_HEIGHT_PX();
    InicioJuego(QWidget *parent = nullptr);
    ~InicioJuego();

private slots:
    void on_playButton_clicked();

private:
    Ui::InicioJuego *ui;
};
#endif // INICIOJUEGO_H
