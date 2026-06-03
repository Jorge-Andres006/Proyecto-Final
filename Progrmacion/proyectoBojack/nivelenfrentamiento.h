#ifndef NIVELENFRENTAMIENTO_H
#define NIVELENFRENTAMIENTO_H

#include "nivel.h"
#include "jugador.h"
#include "disco.h"
#include "arco.h"
#include "rival.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>

class NivelEnfrentamiento : public Nivel
{
private:
    static constexpr double LIMITE_IZQUIERDO = 120.0;

    static constexpr double LIMITE_DERECHO = 1150.0;

    static constexpr double LIMITE_SUPERIOR = 80.0;

    static constexpr double LIMITE_INFERIOR = 600.0;
    Jugador jugador;

    Rival rival;

    Disco disco;

    Arco arcoJugador;

    Arco arcoRival;

    QGraphicsScene* scene;

    int golesJugador;

    int golesRival;
    Vector2D direccionJugador;

    double potencia;

    bool cargandoDisparo;

    bool tieneDisco;

    double tiempoRecogerDisco;
    int frameActual;
    int frameRival;
    double tiempoAnimacionRival;
    double tiempoAnimacion;
    bool disparando;

    bool disparoPendiente;

    int frameDisparo;

    double tiempoDisparo;

    double potenciaDisparo;

    Vector2D direccionDisparo;
    QGraphicsPixmapItem* itemJugador;
    QGraphicsPixmapItem* itemRival;

    QPixmap spriteSheet;

    QPixmap spriteSheetObstaculos;
    QPixmap spriteSheetRival;
    QPixmap spriteSheetDisparo;
    QGraphicsPixmapItem* itemDisco;

    QPixmap spriteSheetDisco;
    QPixmap discoVertical;
    QPixmap discoHorizontal;

    QGraphicsPixmapItem* hudPotencia;
    QGraphicsRectItem* barraPotencia;

    QGraphicsRectItem* itemArcoJugador;
    QGraphicsRectItem* itemArcoRival;

    bool disparoParabolico;
    bool proyectilActivo;

    double tiempoProyectil;

    Vector2D posicionInicialProyectil;
    QGraphicsTextItem* textoCronometro;
    double velocidadInicialProyectil;
    bool rivalDisparando;
    double tiempoDisparoRival;

    double tiempoObstaculos;
    std::vector<QGraphicsPixmapItem*> itemsObstaculos;
    std::vector<Vector2D> posicionesObstaculos;

    static constexpr double GRAVEDAD = 100;
    static constexpr double ANGULO_PARABOLICO = 45.0;
    const double RANGO_ROBO = 40.3;



public:

    NivelEnfrentamiento(
        double ancho,
        double alto,
        QGraphicsScene* scene
        );

    ~NivelEnfrentamiento();

    void iniciar() override;

    void actualizar(double dt) override;

    void finalizar() override;
    void moverJugador(const Vector2D& direccion);

    void iniciarCarga();

    void detenerCarga();

    void actualizarDisparo(double dt);

    double getPotencia() const;
    void verificarGol();
    void reiniciarDisco();
    void activarDisparoParabolico();
    void intentarRobo();

    void generarObstaculos();
    void eliminarObstaculos();
};

#endif
