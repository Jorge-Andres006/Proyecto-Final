#include "powerup.h"

PowerUp::PowerUp(
    TipoPowerUp tipo,
    const Vector2D& posicion
    )
    :
    Entidad(
        posicion,
        Vector2D(0,0),
        20.0
        )
{
    tipoPowerUp = tipo;
    activo = true;
}

void PowerUp::actualizar(double dt)
{
}

TipoEntidad PowerUp::getTipo() const
{
    return POWERUP;
}

TipoPowerUp PowerUp::getTipoPowerUp() const
{
    return tipoPowerUp;
}

bool PowerUp::estaActivo() const
{
    return activo;
}

void PowerUp::desactivar()
{
    activo = false;
}
