#ifndef MUNDO_H
#define MUNDO_H

#include <vector>

#include "entidad.h"

    class Mundo
{
private:

    std::vector<Entidad*> entidades;

    double ancho;
    double alto;

public:

    Mundo(double ancho, double alto);

    void agregarEntidad(Entidad* entidad);

    void actualizar(double dt);

private:

    void actualizarEntidades(double dt);

    void manejarColisiones();

    void manejarLimites();
};

#endif


