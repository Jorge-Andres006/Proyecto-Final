#include "arco.h"

using namespace std;

Arco::Arco() {

    posicion = Vector2D();

    ancho = 20.0;

    alto = 10.0;
}
Arco::~Arco() {}
Arco::Arco(const Vector2D &posicion,double ancho,double alto) {

    this->posicion = posicion;

    this->ancho = ancho;

    this->alto = alto;
}

bool Arco::detectarGol(const Disco &disco) const
{
    Vector2D posDisco = disco.getPosicion();

    double radio = disco.getRadio();

    bool dentroX =
        (posDisco.getX() + radio >= posicion.getX()) &&
        (posDisco.getX() - radio <= posicion.getX() + ancho);

    bool dentroY =
        (posDisco.getY() + radio >= posicion.getY()) &&
        (posDisco.getY() - radio <= posicion.getY() + alto);

    bool vieneDeFrente =
        disco.getVelocidad().getX() > 0;

    return (dentroX && dentroY && vieneDeFrente);
}
Vector2D Arco::getPosicion() const {

    return posicion;
}

double Arco::getAncho() const {

    return ancho;
}

double Arco::getAlto() const {

    return alto;
}

void Arco::setPosicion(const Vector2D &posicion) {

    this->posicion = posicion;
}

void Arco::setAncho(double ancho) {

    this->ancho = ancho;
}

void Arco::setAlto(double alto) {

    this->alto = alto;
}
