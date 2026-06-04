#ifndef ENTIDAD_H
#define ENTIDAD_H

#include "vector2d.h"
enum TipoEntidad
{
    JUGADOR,
    DISCO,
    OBSTACULO,
    RIVAL,
    POWERUP
};
class Entidad {
protected:
    Vector2D posicion;
    Vector2D velocidad;

    double radio;

public:
    // Constructores
    Entidad();

    Entidad(const Vector2D &posicion, const Vector2D &velocidad, double radio);

    // Destructor virtual
    virtual ~Entidad();

    // Método abstracto
    virtual void actualizar(double dt) = 0;
    virtual TipoEntidad getTipo() const = 0;
    // Movimiento genérico
    void mover(double dt);

    // Colisión circular
    bool colisionaCon(const Entidad &otra) const;

    // Getters
    Vector2D getPosicion() const;
    Vector2D getVelocidad() const;
    double getRadio() const;

    // Setters
    void setPosicion(const Vector2D &posicion);
    void setVelocidad(const Vector2D &velocidad);
    void setRadio(double radio);
};

#endif
