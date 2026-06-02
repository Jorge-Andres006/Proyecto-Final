#ifndef NIVELENTRENAMIENTO_H
#define NIVELENTRENAMIENTO_H

#include <vector>

#include "nivel.h"
#include "jugador.h"
#include "disco.h"
#include "arco.h"
#include "obstaculo.h"
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QAudioOutput>

class NivelEntrenamiento : public Nivel
{
private:

    Jugador jugador;

    Disco disco;

    Arco arco;

    QPixmap spriteSheetObstaculos;
    std::vector<Obstaculo*> obstaculos;
    std::vector<QGraphicsPixmapItem*> itemsObstaculos;

    int goles;
    double tiempoSpawnObstaculos;
    double tiempoRecogerDisco;

    Vector2D direccionJugador;

    double potencia;

    bool cargandoDisparo;
    static constexpr double LIMITE_IZQUIERDO = 80.0;

    static constexpr double LIMITE_DERECHO = 1200.0;

    static constexpr double LIMITE_SUPERIOR = 80.0;

    static constexpr double LIMITE_INFERIOR = 640.0;
    bool tieneDisco;
    void verificarGol();
    bool invulnerable;
    double tiempoInvulnerabilidad;
    void generarObstaculo();
    QGraphicsScene *scene;


    QGraphicsPixmapItem *itemJugador;
    QPixmap spriteSheet;

    QGraphicsPixmapItem* itemDisco;
    QPixmap spriteSheetDisco;

    QGraphicsRectItem *itemArco;
    QGraphicsPixmapItem* hudPotencia;

    QGraphicsRectItem* barraPotencia;
    QGraphicsPixmapItem* hudGolesItem;
    int frameActual;

    double tiempoAnimacion;
    bool disparando;

    int frameDisparo;

    double tiempoDisparo;
    bool disparoPendiente;

    double potenciaDisparo;

    Vector2D direccionDisparo;
    QPixmap spriteSheetDisparo;

    QPixmap discoVertical;
    QPixmap discoHorizontal;
    QMediaPlayer* sonidoTodd;

    QAudioOutput* audioTodd;
    QMediaPlayer* sonidoGol;

    QAudioOutput* audioGol;
public:
    void moverJugador(
        const Vector2D& direccion
        );
    NivelEntrenamiento(double ancho, double alto, QGraphicsScene *scene);

    ~NivelEntrenamiento();

    void iniciar() override;

    void actualizar(double dt) override;

    void finalizar() override;
    Jugador& getJugador();

    Disco& getDisco();

    void iniciarCarga();

    void detenerCarga();


    double getPotencia() const;
    int getGoles() const;
    void actualizarDisparo(double dt);

};

#endif
