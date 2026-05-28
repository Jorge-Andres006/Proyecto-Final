#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "entidad.h"

class Obstaculo : public Entidad
{
private:

    bool activo;

public:

    Obstaculo();
    ~Obstaculo();
    Obstaculo(const Vector2D &posicion,double radio);

    void actualizar(double dt) override;

    bool estaActivo() const;

    void desactivar();

    void activar();
};

#endif
