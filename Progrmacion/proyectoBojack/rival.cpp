#include "rival.h"

using namespace std;

Rival::Rival() : Personaje() {

    posicionDisco = Vector2D();

    posicionJugador = Vector2D();

    distanciaDisco = 0.0;

    debeAtacar = false;

    ataquesExitosos = 0;

    ataquesFallidos = 0;
}
Rival::~Rival(){

}
Rival::Rival(const Vector2D &posicion,double radio,double velocidadMaxima,double aceleracion,double fuerzaDisparo,double alcanceGolpe): Personaje(posicion,radio,velocidadMaxima,aceleracion,fuerzaDisparo,alcanceGolpe) {

    posicionDisco = Vector2D();

    posicionJugador = Vector2D();

    distanciaDisco = 0.0;

    debeAtacar = false;

    ataquesExitosos = 0;

    ataquesFallidos = 0;
}

void Rival::actualizar(double dt) {

    Personaje::actualizar(dt);
}

void Rival::percibir(const Disco &disco,const Personaje &jugador) {

    posicionDisco = disco.getPosicion();

    posicionJugador = jugador.getPosicion();

    distanciaDisco = posicion.distancia(posicionDisco);
}

void Rival::razonar() {

    if (distanciaDisco <= alcanceGolpe) {

        debeAtacar = true;
    }

    else {

        debeAtacar = false;
    }
}

void Rival::actuar(Disco &disco, double dt) {

    Vector2D direccion = posicionDisco - posicion;

    if (debeAtacar) {

        Vector2D direccionDisparo = posicionJugador - posicion;

        disparar(disco, direccionDisparo);
    }

    else {

        moverEnDireccion(direccion, dt);
    }
}

void Rival::aprender() {

    if (ataquesFallidos > ataquesExitosos) {

        fuerzaDisparo *= 0.99;
    }

    else if (ataquesExitosos > ataquesFallidos) {

        fuerzaDisparo *= 1.01;
    }

    if (fuerzaDisparo < 5.0) {

        fuerzaDisparo = 5.0;
    }

    if (fuerzaDisparo > 40.0) {

        fuerzaDisparo = 40.0;
    }
}

bool Rival::getDebeAtacar() const {

    return debeAtacar;
}
TipoEntidad Rival::getTipo() const
{
    return RIVAL;
}
