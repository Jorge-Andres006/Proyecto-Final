#include "nivelEntrenamiento.h"

using namespace std;

NivelEntrenamiento::NivelEntrenamiento(double ancho, double alto)
    : Nivel(ancho, alto),

    jugador("Bojack",
            Vector2D(ancho / 2.0, alto - 15.0),
            5.0,
            10.0,
            5.0,
            20.0,
            10.0),

    disco(Vector2D(ancho / 2.0, alto / 2.0),
          Vector2D(0.0, 0.0),
          3.0,
          1.0,
          0.98,
          0.8,
          30.0),

    arco(Vector2D(ancho / 2.0 - 15.0, 5.0),
         30.0,
         5.0) {

    goles = 0;

    tiempoSpawnObstaculos = 0.0;
}

NivelEntrenamiento::~NivelEntrenamiento() {}

void NivelEntrenamiento::iniciar() {

    mundo.agregarEntidad(&jugador);

    mundo.agregarEntidad(&disco);
}

void NivelEntrenamiento::actualizar(double dt) {

    tiempo += dt;

    tiempoSpawnObstaculos += dt;

    mundo.actualizar(dt);

    verificarGol();

    if (tiempoSpawnObstaculos >= 5.0) {

        generarObstaculo();

        tiempoSpawnObstaculos = 0.0;
    }
}

void NivelEntrenamiento::finalizar() {

    terminado = true;
}

void NivelEntrenamiento::verificarGol() {

    if (arco.detectarGol(disco)) {

        goles++;

        disco.setPosicion(Vector2D(50.0, 50.0));

        disco.setVelocidad(Vector2D(0.0, 0.0));
    }
}

void NivelEntrenamiento::generarObstaculo() {

    double x = 20.0 + (rand() % 60);

    double y = 20.0 + (rand() % 20);

    Obstaculo obstaculo(
        Vector2D(x, y),
        4.0
        );

    obstaculos.push_back(obstaculo);

    mundo.agregarEntidad(&obstaculos.back());
}
Jugador& NivelEntrenamiento::getJugador() {

    return jugador;
}

Disco& NivelEntrenamiento::getDisco() {

    return disco;
}
