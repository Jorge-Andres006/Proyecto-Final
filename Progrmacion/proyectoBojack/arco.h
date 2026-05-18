#ifndef ARCO_H
#define ARCO_H

#include "disco.h"
#include "vector2d.h"

class Arco
{
private:

    Vector2D posicion;

    double ancho;

    double alto;

public:

    Arco();
    ~Arco();
    Arco(const Vector2D &posicion,double ancho,double alto);

    bool detectarGol(const Disco &disco) const;

    Vector2D getPosicion() const;

    double getAncho() const;

    double getAlto() const;

    void setPosicion(const Vector2D &posicion);

    void setAncho(double ancho);

    void setAlto(double alto);
};

#endif
