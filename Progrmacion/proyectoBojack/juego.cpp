#include "juego.h"

#include <QPixmap>
#include <QGraphicsTextItem>
#include <QFont>
#include <QRect>

Juego::Juego(
    QGraphicsScene *scene,
    QObject *parent)
    : QObject(parent)
{
    this->scene = scene;

    fondo = nullptr;
    nivel1 = nullptr;
    nivel2 = nullptr;
    barraCarga = nullptr;
    barraCargaFondo = nullptr;

    timerCarga = nullptr;

    progresoCarga = 0;

    nivelPendiente = 0;

    cargando = false;
    timerJuego = new QTimer(this);

    connect(
        timerJuego,
        &QTimer::timeout,
        this,
        &::Juego::actualizarJuego
        );
    teclaW = false;
    teclaA = false;
    teclaS = false;
    teclaD = false;
    victoriaMostrada=false;
}

void Juego::mostrarMenu()
{
    timerJuego->stop();


    if(nivel1)
    {
        delete nivel1;
        nivel1 = nullptr;
    }
    if(nivel2)
    {
        delete nivel2;
        nivel2 = nullptr;
    }
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
    victoriaMostrada = false;

    timerJuego->stop();

    if(nivel2)
    {
        delete nivel2;
        nivel2 = nullptr;
    }

    if(nivel1)
    {
        delete nivel1;
        nivel1 = nullptr;
    }

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

    fondo = scene->addPixmap(
        fondoNivel1
        );

    fondo->setZValue(-100);

    scene->setSceneRect(
        fondoNivel1.rect()
        );

    nivel1 = new NivelEntrenamiento(
        1280,
        720,
        scene
        );

    nivel1->iniciar();

    timerJuego->start(16);
}

void Juego::iniciarNivel2()
{
    victoriaMostrada = false;

    timerJuego->stop();

    if(nivel1)
    {
        delete nivel1;

        nivel1 = nullptr;
    }

    if(nivel2)
    {
        delete nivel2;
        nivel2 = nullptr;
    }

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

    fondo = scene->addPixmap(
        fondoNivel2
        );

    fondo->setZValue(-100);

    scene->setSceneRect(
        fondoNivel2.rect()
        );

    nivel2 = new NivelEnfrentamiento(
        1280,
        720,
        scene
        );

    nivel2->iniciar();

    timerJuego->start(16);
}

void Juego::mostrarPantallaCarga(int nivel)
{

    timerJuego->stop();
    if(cargando){

        return;
    }

    cargando = true;

    if(timerCarga)
    {
        timerCarga->stop();

        timerCarga->deleteLater();

        timerCarga = nullptr;
    }

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

    QGraphicsTextItem *textoCarga =
        scene->addText("Cargando...");

    QFont fuente(
        "Segoe UI",
        20,
        QFont::Bold
        );

    textoCarga->setFont(fuente);

    textoCarga->setDefaultTextColor(
        QColor(0,0,0)
        );

    qreal anchoTexto =
        textoCarga->boundingRect().width();

    textoCarga->setPos(
        1105 - anchoTexto/2,
        625
        );


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
        cargando = false;
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
void Juego::teclaPresionada(int tecla)
{
    if(!nivel1 && !nivel2)
    {
        return;
    }
    switch(tecla)
    {
    case Qt::Key_W:

        teclaW = true;

        break;

    case Qt::Key_S:

        teclaS = true;

        break;

    case Qt::Key_A:

        teclaA = true;

        break;

    case Qt::Key_D:

        teclaD = true;

        break;

    case Qt::Key_R:

        if(nivel1)
        {
            nivel1->iniciarCarga();
        }

        if(nivel2)
        {
            if(teclaShift)
            {
                nivel2->activarDisparoParabolico();
            }

            nivel2->iniciarCarga();
        }

        break;
    case Qt::Key_Shift:

        teclaShift = true;

        break;
    case Qt::Key_C:

        teclaC = true;

        break;
    }

}
void Juego::teclaLiberada(int tecla)
{
    if(!nivel1 && !nivel2)
    {
        return;
    }

    switch(tecla)
    {
    case Qt::Key_W:

        teclaW = false;

        break;

    case Qt::Key_S:

        teclaS = false;

        break;

    case Qt::Key_A:

        teclaA = false;

        break;

    case Qt::Key_D:

        teclaD = false;

        break;

    case Qt::Key_R:

        if(nivel1)
        {
            nivel1->detenerCarga();
        }

        if(nivel2)
        {
            nivel2->detenerCarga();
        }

        break;
    case Qt::Key_Shift:

        teclaShift = false;

        break;
    case Qt::Key_C:

        teclaC = false;

        break;
    }


}
void Juego::actualizarJuego()
{
    if(!nivel1 && !nivel2)
    {
        return;
    }

    Vector2D direccion(0,0);

    if(teclaW)
    {
        direccion += Vector2D(0,-3);
    }

    if(teclaS)
    {
         direccion += Vector2D(0,3);
    }

    if(teclaA)
    {
        direccion += Vector2D(-3,0);
    }

    if(teclaD)
    {
        direccion += Vector2D(3,0);
    }

    if(direccion.getX() != 0 ||direccion.getY() != 0)
    {
        if(nivel1)
        {
            nivel1->moverJugador(
                direccion
                );
        }

        if(nivel2)
        {
            nivel2->moverJugador(
                direccion
                );
        }
    }
    if(teclaC && nivel2)
    {
        nivel2->intentarRobo();
    }

    if(nivel1)
    {
        nivel1->actualizar(0.016);
    }

    if(nivel2)
    {
        nivel2->actualizar(0.016);
    }
    if(nivel1)
    {
        emit golesActualizados(
            nivel1->getGoles()
            );
    }
    if(
        nivel1 &&
        nivel1->estaTerminado()
        &&
        !victoriaMostrada
        )
    {
        victoriaMostrada = true;

        if(nivel1->getPerdio())
        {
            emit jugadorPerdio();
        }
        else
        {
            emit nivelCompletado();
        }
    }

}
NivelEntrenamiento* Juego::getNivel1()
{
    return nivel1;
}
void Juego::pausarJuego()
{
    timerJuego->stop();
}
