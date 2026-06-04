#ifndef POWERUP_H
#define POWERUP_H

#include "entidad.h"

enum TipoPowerUp
{
    ALGODON,
    WHISKY,
    BOJACK
};

class PowerUp : public Entidad
{
private:

    TipoPowerUp tipoPowerUp;
    bool activo;

public:

    PowerUp(
        TipoPowerUp tipo,
        const Vector2D& posicion
        );

    void actualizar(double dt) override;

    TipoEntidad getTipo() const override;

    TipoPowerUp getTipoPowerUp() const;

    bool estaActivo() const;

    void desactivar();
};

#endif
