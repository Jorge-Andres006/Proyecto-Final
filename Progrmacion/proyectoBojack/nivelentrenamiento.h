#ifndef NIVELENTRENAMIENTO_H
#define NIVELENTRENAMIENTO_H

#include <vector>

#include "nivel.h"
#include "jugador.h"
#include "disco.h"
#include "arco.h"
#include "obstaculo.h"

class NivelEntrenamiento : public Nivel
{
private:

    Jugador jugador;

    Disco disco;

    Arco arco;

    std::vector<Obstaculo> obstaculos;

    int goles;

    double tiempoSpawnObstaculos;

public:

    NivelEntrenamiento(double ancho, double alto);

    ~NivelEntrenamiento();

    void iniciar() override;

    void actualizar(double dt) override;

    void finalizar() override;
    Jugador& getJugador();

    Disco& getDisco();
private:

    void verificarGol();

    void generarObstaculo();
};

#endif
