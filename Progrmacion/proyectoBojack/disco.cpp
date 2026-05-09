#include "disco.h"

using namespace std;

Disco::Disco() : Entidad() {

    masa = MASA_BASE;

    friccion = FRICCION_BASE;

    rebote = REBOTE_BASE;

    velocidadMaxima = VELOCIDAD_MAXIMA_BASE;
}

Disco::Disco(const Vector2D &posicion, const Vector2D &velocidad, double radio,
             double masa, double friccion, double rebote,
             double velocidadMaxima)
    : Entidad(posicion, velocidad, radio) {

    this->masa = masa;

    this->friccion = friccion;

    this->rebote = rebote;

    this->velocidadMaxima = velocidadMaxima;
}

void Disco::actualizar(double dt) {

    aplicarFriccion();

    limitarVelocidad();

    mover(dt);
}

void Disco::aplicarImpulso(const Vector2D &impulso) {

    velocidad += impulso / masa;
}

void Disco::aplicarFriccion() {

    velocidad *= friccion;

    // Evita micro-movimientos infinitos
    if (velocidad.magnitud() < 0.01) {
        velocidad.setXY(0.0, 0.0);
    }
}

void Disco::rebotarX() { velocidad.setX(-velocidad.getX() * rebote); }

void Disco::rebotarY() { velocidad.setY(-velocidad.getY() * rebote); }

void Disco::limitarVelocidad() { velocidad.limitar(velocidadMaxima); }

double Disco::getMasa() const { return masa; }

double Disco::getFriccion() const { return friccion; }

double Disco::getRebote() const { return rebote; }

double Disco::getVelocidadMaxima() const { return velocidadMaxima; }

void Disco::setMasa(double masa) { this->masa = masa; }

void Disco::setFriccion(double friccion) { this->friccion = friccion; }

void Disco::setRebote(double rebote) { this->rebote = rebote; }

void Disco::setVelocidadMaxima(double velocidadMaxima) {
    this->velocidadMaxima = velocidadMaxima;
}
