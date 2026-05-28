#include "juego.h"

#include <QPixmap>

Juego::Juego(QGraphicsScene *scene)
{
    this->scene = scene;
}

void Juego::mostrarMenu()
{
    scene->clear();

    QPixmap fondoOriginal(
        ":/new/prefix1/Imagenes/FondoMenu.png"
        );

    QPixmap fondoEscalado =
        fondoOriginal.scaled(
            1280,
            720,
            Qt::IgnoreAspectRatio,
            Qt::SmoothTransformation
            );

    fondo = scene->addPixmap(fondoEscalado);

    fondo->setZValue(-100);

    scene->setSceneRect(
        fondo->boundingRect()
        );
}

void Juego::iniciarNivel1()
{
    scene->clear();

    QPixmap fondoOriginal(
        ":/new/prefix1/Imagenes/FondoMenu.png"
        );

    QPixmap fondoNivel1 =
        fondoOriginal.scaled(
            1280,
            720,
            Qt::IgnoreAspectRatio,
            Qt::SmoothTransformation
            );
    fondo = scene->addPixmap(fondoNivel1);

    fondo->setZValue(-100);

    scene->setSceneRect(
        fondoNivel1.rect()
        );
}

void Juego::iniciarNivel2()
{
    scene->clear();

    QPixmap fondoOriginal(
        ":/new/prefix1/Imagenes/FondoMenu.png"
        );

    QPixmap fondoNivel2 =
        fondoOriginal.scaled(
            1280,
            720,
            Qt::IgnoreAspectRatio,
            Qt::SmoothTransformation
            );
    fondo = scene->addPixmap(fondoNivel2);

    fondo->setZValue(-100);

    scene->setSceneRect(
        fondoNivel2.rect()
        );
}

