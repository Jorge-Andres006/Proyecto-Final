#ifndef JUEGO_H
#define JUEGO_H

#include <QGraphicsScene>

#include <QGraphicsPixmapItem>

class Juego
{
public:

    Juego(QGraphicsScene *scene);

    void mostrarMenu();

    void iniciarNivel1();

    void iniciarNivel2();

private:

    QGraphicsScene *scene;

    QGraphicsPixmapItem *fondo;

    int anchoMapa;

    int altoMapa;
};

#endif

