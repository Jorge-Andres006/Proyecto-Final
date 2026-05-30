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
    void actualizarEntidades(double dt);

    void manejarColisiones();

    void manejarLimites();
public:
    void eliminarEntidad(Entidad* entidad);
    Mundo(double ancho, double alto);

    void agregarEntidad(Entidad* entidad);

    void actualizar(double dt);


};

#endif


