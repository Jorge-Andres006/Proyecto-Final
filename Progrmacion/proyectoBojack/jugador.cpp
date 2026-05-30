#include "jugador.h"

using namespace std;

Jugador::Jugador() : Personaje() {

    nombre = "Jugador";

    puntuacion = 0;
}
Jugador::~Jugador(){

}
Jugador::Jugador(const string &nombre,const Vector2D &posicion,double radio,double velocidadMaxima,double aceleracion,double fuerzaDisparo,double alcanceGolpe): Personaje(posicion,radio,velocidadMaxima,aceleracion,fuerzaDisparo,alcanceGolpe) {

    this->nombre = nombre;

    puntuacion = 0;
}

void Jugador::actualizar(double dt) {

    Personaje::actualizar(dt);
}

void Jugador::sumarPunto() {

    puntuacion++;
}

string Jugador::getNombre() const {

    return nombre;
}

int Jugador::getPuntuacion() const {

    return puntuacion;
}

void Jugador::setNombre(const string &nombre) {

    this->nombre = nombre;
}
TipoEntidad Jugador::getTipo() const
{
    return JUGADOR;
}
