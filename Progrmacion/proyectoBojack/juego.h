#ifndef JUEGO_H
#define JUEGO_H

#include <QObject>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QMediaPlayer>

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

signals:

    void nivelCargado(int nivel);

private slots:

    void actualizarCarga();


private:

    QGraphicsScene *scene;

    QGraphicsPixmapItem *fondo;

    int anchoMapa;
    int altoMapa;

    QGraphicsRectItem *barraCargaFondo;

    QGraphicsRectItem *barraCarga;

    QTimer *timerCarga;

    int progresoCarga;

    int nivelPendiente;

    QMediaPlayer *musicaMenu;
};

#endif
