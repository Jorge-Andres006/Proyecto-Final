#ifndef JUEGO_H
#define JUEGO_H

#include <QObject>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QMediaPlayer>
#include "nivelEntrenamiento.h"
#include "nivelenfrentamiento.h"

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
    void pausarJuego();
signals:

    void nivelCargado(int nivel);
    void golesActualizados(int goles);
    void nivelCompletado();

private slots:
    void actualizarJuego();
    void actualizarCarga();

private:
    NivelEntrenamiento *nivel1;
    NivelEnfrentamiento* nivel2;

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



    bool cargando;
    bool teclaW;
    bool teclaA;
    bool teclaS;
    bool teclaD;
    bool teclaShift;
    bool teclaC;

    bool victoriaMostrada;

};

#endif
