#ifndef NIVEL_H
#define NIVEL_H

#include "mundo.h"

class Nivel
{
protected:

    Mundo mundo;

    double tiempo;

    bool terminado;

public:

    Nivel(double ancho, double alto);

    virtual ~Nivel();

    virtual void iniciar() = 0;

    virtual void actualizar(double dt) = 0;

    virtual void finalizar() = 0;

    bool estaTerminado() const;

    double getTiempo() const;
};

#endif
