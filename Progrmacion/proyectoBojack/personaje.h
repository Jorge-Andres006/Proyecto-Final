#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "entidad.h"
#include "disco.h"

class Personaje : public Entidad
{
protected:

    double velocidadMaxima;

    double aceleracion;

    double fuerzaDisparo;

    double alcanceGolpe;

public:

    static constexpr double VELOCIDAD_MAXIMA_BASE = 10.0;

    static constexpr double ACELERACION_BASE = 5.0;

    static constexpr double FUERZA_DISPARO_BASE = 20.0;

    static constexpr double ALCANCE_GOLPE_BASE = 8.0;

    Personaje();
    Personaje(const Vector2D &posicion,double radio,double velocidadMaxima,double aceleracion,double fuerzaDisparo,double alcanceGolpe);

    virtual ~Personaje();

    void actualizar(double dt) override;

    void moverEnDireccion(const Vector2D &direccion, double dt);

    void frenar();

    void limitarVelocidad();

    void disparar(Disco &disco, const Vector2D &direccion);

    bool puedeGolpear(const Disco &disco) const;

    double getVelocidadMaxima() const;

    double getAceleracion() const;

    double getFuerzaDisparo() const;

    double getAlcanceGolpe() const;

    void setVelocidadMaxima(double velocidadMaxima);

    void setAceleracion(double aceleracion);

    void setFuerzaDisparo(double fuerzaDisparo);

    void setAlcanceGolpe(double alcanceGolpe);
};

#endif
