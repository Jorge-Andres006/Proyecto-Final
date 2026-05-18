#include "personaje.h"

using namespace std;

Personaje::Personaje() : Entidad() {

    velocidadMaxima = VELOCIDAD_MAXIMA_BASE;

    aceleracion = ACELERACION_BASE;

    fuerzaDisparo = FUERZA_DISPARO_BASE;

    alcanceGolpe = ALCANCE_GOLPE_BASE;
}

Personaje::Personaje(const Vector2D &posicion, double radio,double velocidadMaxima, double aceleracion,double fuerzaDisparo, double alcanceGolpe): Entidad(posicion, Vector2D(0.0, 0.0), radio) {

    this->velocidadMaxima = velocidadMaxima;

    this->aceleracion = aceleracion;

    this->fuerzaDisparo = fuerzaDisparo;

    this->alcanceGolpe = alcanceGolpe;
}

Personaje::~Personaje() {}

void Personaje::actualizar(double dt) {

    limitarVelocidad();

    mover(dt);

    frenar();
}

void Personaje::moverEnDireccion(const Vector2D &direccion, double dt) {

    Vector2D dirNormalizada = direccion.normalizar();

    velocidad += dirNormalizada * aceleracion * dt;
}

void Personaje::frenar() {

    velocidad *= 0.90;

    if (velocidad.magnitud() < 0.01) {

        velocidad.setXY(0.0, 0.0);
    }
}

void Personaje::limitarVelocidad() {

    velocidad.limitar(velocidadMaxima);
}

void Personaje::disparar(Disco &disco, const Vector2D &direccion) {

    if (!puedeGolpear(disco)) {
        return;
    }

    Vector2D dirNormalizada = direccion.normalizar();

    Vector2D impulso = dirNormalizada * fuerzaDisparo;

    disco.aplicarImpulso(impulso);
}

bool Personaje::puedeGolpear(const Disco &disco) const {

    double distancia = posicion.distancia(disco.getPosicion());

    return (distancia <= alcanceGolpe);
}

double Personaje::getVelocidadMaxima() const {

    return velocidadMaxima;
}

double Personaje::getAceleracion() const {

    return aceleracion;
}

double Personaje::getFuerzaDisparo() const {

    return fuerzaDisparo;
}

double Personaje::getAlcanceGolpe() const {

    return alcanceGolpe;
}

void Personaje::setVelocidadMaxima(double velocidadMaxima) {

    this->velocidadMaxima = velocidadMaxima;
}

void Personaje::setAceleracion(double aceleracion) {

    this->aceleracion = aceleracion;
}

void Personaje::setFuerzaDisparo(double fuerzaDisparo) {

    this->fuerzaDisparo = fuerzaDisparo;
}

void Personaje::setAlcanceGolpe(double alcanceGolpe) {

    this->alcanceGolpe = alcanceGolpe;
}
