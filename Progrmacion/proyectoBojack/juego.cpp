#include "juego.h"

#include <QPixmap>

Juego::Juego(
    QGraphicsScene *scene,
    QObject *parent)
    : QObject(parent)
{
    this->scene = scene;

    fondo = nullptr;

    barraCarga = nullptr;
    barraCargaFondo = nullptr;

    timerCarga = nullptr;

    progresoCarga = 0;

    nivelPendiente = 0;
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
        ":/new/prefix1/Imagenes/fondoNivel1.png"
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
        ":/new/prefix1/Imagenes/fondoNivel2.png"
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

void Juego::mostrarPantallaCarga(int nivel)
{
    scene->clear();

    nivelPendiente = nivel;

    progresoCarga = 0;

    QPixmap imagen(
        ":/new/prefix1/Imagenes/fondoTransicion.png"
        );

    imagen = imagen.scaled(
        1280,
        720,
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        );

    scene->addPixmap(imagen);

    barraCargaFondo =
        scene->addRect(
            980,
            660,
            250,
            20,
            QPen(QColor(180,180,180)),
            QBrush(QColor(40,40,40))
            );

    barraCarga =
        scene->addRect(
            980,
            660,
            0,
            20,
            Qt::NoPen,
            QBrush(QColor(95,168,211))
            );

    timerCarga = new QTimer();

    connect(
        timerCarga,
        &QTimer::timeout,
        this,
        &Juego::actualizarCarga
        );

    timerCarga->start(25);
}



void Juego::actualizarCarga()
{
    progresoCarga++;

    barraCarga->setRect(
        980,
        660,
        progresoCarga * 2.5,
        20
        );

    if(progresoCarga >= 100)
    {
        timerCarga->stop();
        timerCarga->deleteLater();

        timerCarga = nullptr;

        emit nivelCargado(nivelPendiente);

        if(nivelPendiente == 1)
        {
            iniciarNivel1();
        }
        else
        {
            iniciarNivel2();
        }
    }
}
