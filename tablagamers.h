#ifndef TABLAGAMERS_H
#define TABLAGAMERS_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QVector>
#include <QPixmap>
#include <QFile>
#include <QDir>
#include "user.h"

namespace Ui {
class TablaGamers;
}

class TablaGamers : public QMainWindow
{
    Q_OBJECT

public:
    explicit TablaGamers(QWidget *parent = nullptr);
    static void addUser(User &account);
    static int findUser(User &account);
    static void updateUser(int index, int time);
    void mergeSort(QVector<User> &vec, int start, int end);
    void merge(QVector<User> &vec, int start, int middle, int end);
    ~TablaGamers();

private slots:
    void on_closeButton_clicked();

private:
    Ui::TablaGamers *ui;
};

#endif // TABLAGAMERS_H
