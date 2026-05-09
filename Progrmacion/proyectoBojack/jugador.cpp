#include "jugador.h"

using namespace std;

Jugador::Jugador() : Entidad() {

    nombre = "Jugador";

    puntuacion = 0;

    velocidadMaxima = VELOCIDAD_MAXIMA_BASE;

    aceleracion = ACELERACION_BASE;

    fuerzaDisparo = FUERZA_DISPARO_BASE;

    alcanceGolpe = ALCANCE_GOLPE_BASE;
}

Jugador::Jugador(const string &nombre, const Vector2D &posicion, double radio,
                 double velocidadMaxima, double aceleracion,
                 double fuerzaDisparo, double alcanceGolpe)
    : Entidad(posicion, Vector2D(0.0, 0.0), radio) {

    this->nombre = nombre;

    puntuacion = 0;

    this->velocidadMaxima = velocidadMaxima;

    this->aceleracion = aceleracion;

    this->fuerzaDisparo = fuerzaDisparo;

    this->alcanceGolpe = alcanceGolpe;
}

void Jugador::actualizar(double dt) {

    limitarVelocidad();

    mover(dt);

    frenar();
}

void Jugador::moverEnDireccion(const Vector2D &direccion, double dt) {

    Vector2D dirNormalizada = direccion.normalizar();

    velocidad += dirNormalizada * aceleracion * dt;
}

void Jugador::frenar() {

    velocidad *= 0.90;

    if (velocidad.magnitud() < 0.01) {
        velocidad.setXY(0.0, 0.0);
    }
}

void Jugador::limitarVelocidad() { velocidad.limitar(velocidadMaxima); }

void Jugador::disparar(Disco &disco, const Vector2D &direccion) {

    if (!puedeGolpear(disco)) {
        return;
    }

    Vector2D dirNormalizada = direccion.normalizar();

    Vector2D impulso = dirNormalizada * fuerzaDisparo;

    disco.aplicarImpulso(impulso);
}

bool Jugador::puedeGolpear(const Disco &disco) const {

    double distancia = posicion.distancia(disco.getPosicion());

    return (distancia <= alcanceGolpe);
}

void Jugador::sumarPunto() { puntuacion++; }

string Jugador::getNombre() const { return nombre; }

int Jugador::getPuntuacion() const { return puntuacion; }

double Jugador::getVelocidadMaxima() const { return velocidadMaxima; }

double Jugador::getAceleracion() const { return aceleracion; }

double Jugador::getFuerzaDisparo() const { return fuerzaDisparo; }

double Jugador::getAlcanceGolpe() const { return alcanceGolpe; }

void Jugador::setNombre(const string &nombre) { this->nombre = nombre; }

void Jugador::setVelocidadMaxima(double velocidadMaxima) {
    this->velocidadMaxima = velocidadMaxima;
}

void Jugador::setAceleracion(double aceleracion) {
    this->aceleracion = aceleracion;
}

void Jugador::setFuerzaDisparo(double fuerzaDisparo) {
    this->fuerzaDisparo = fuerzaDisparo;
}

void Jugador::setAlcanceGolpe(double alcanceGolpe) {
    this->alcanceGolpe = alcanceGolpe;
}
