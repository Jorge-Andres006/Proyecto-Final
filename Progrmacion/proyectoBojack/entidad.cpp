#include "entidad.h"

using namespace std;

Entidad::Entidad() {
    posicion = Vector2D();
    velocidad = Vector2D();
    radio = 0.0;
}

Entidad::Entidad(const Vector2D &posicion, const Vector2D &velocidad,
                 double radio) {
    this->posicion = posicion;
    this->velocidad = velocidad;
    this->radio = radio;
}

Entidad::~Entidad() {}

void Entidad::mover(double dt) { posicion += velocidad * dt; }

bool Entidad::colisionaCon(const Entidad &otra) const {

    double distanciaCentros = posicion.distancia(otra.posicion);

    return (distanciaCentros <= (radio + otra.radio));
}

Vector2D Entidad::getPosicion() const { return posicion; }

Vector2D Entidad::getVelocidad() const { return velocidad; }

double Entidad::getRadio() const { return radio; }

void Entidad::setPosicion(const Vector2D &posicion) {
    this->posicion = posicion;
}

void Entidad::setVelocidad(const Vector2D &velocidad) {
    this->velocidad = velocidad;
}

void Entidad::setRadio(double radio) { this->radio = radio; }
