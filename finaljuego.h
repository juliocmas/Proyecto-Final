#ifndef FINALJUEGO_H
#define FINALJUEGO_H

#include <QMainWindow>
#include <QPixmap>
#include <QDir>
#include "iniciojuego.h"
#include "tablagamers.h"

namespace Ui {
class FinalJuego;
}

class FinalJuego : public QMainWindow
{
    Q_OBJECT

public:
    explicit FinalJuego(bool win, QWidget *parent = nullptr);
    ~FinalJuego();

private slots:
    void on_playAgainButton_clicked();

    void on_leaderBoardButton_clicked();

private:
    Ui::FinalJuego *ui;
};

#endif // FINALJUEGO_H
