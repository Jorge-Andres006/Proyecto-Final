#ifndef JUEGO_H
#define JUEGO_H

#include <QObject>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QMediaPlayer>
#include "nivelEntrenamiento.h"

class Juego : public QObject
{
    Q_OBJECT

public:

    explicit Juego(
        QGraphicsScene *scene,
        QObject *parent = nullptr
        );

    void mostrarMenu();

    void iniciarNivel1();

    void iniciarNivel2();

    void mostrarPantallaCarga(int nivel);
    NivelEntrenamiento* getNivel1();
    void teclaPresionada(int tecla);
    void teclaLiberada(int tecla);
signals:

    void nivelCargado(int nivel);
    void golesActualizados(int goles);

private slots:
    void actualizarJuego();
    void actualizarCarga();

private:
    NivelEntrenamiento *nivel1;

    QGraphicsScene *scene;

    QTimer *timerJuego;

    QGraphicsPixmapItem *fondo;

    int anchoMapa;
    int altoMapa;

    QGraphicsRectItem *barraCargaFondo;

    QGraphicsRectItem *barraCarga;

    QTimer *timerCarga;

    int progresoCarga;

    int nivelPendiente;

    QMediaPlayer *musicaMenu;

    bool cargando;
    bool teclaW;
    bool teclaA;
    bool teclaS;
    bool teclaD;

};

#endif
