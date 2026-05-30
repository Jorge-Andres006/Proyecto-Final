#include "obstaculo.h"

using namespace std;

Obstaculo::Obstaculo() : Entidad() {

    activo = true;
}

Obstaculo::Obstaculo(const Vector2D &posicion,double radio): Entidad(posicion, Vector2D(0.0, 0.0), radio) {

    activo = true;
}
Obstaculo::~Obstaculo() {}
void Obstaculo::actualizar(double dt) {

    mover(dt);
}

bool Obstaculo::estaActivo() const {

    return activo;
}

void Obstaculo::desactivar() {

    activo = false;
}

void Obstaculo::activar() {

    activo = true;
}
TipoEntidad Obstaculo::getTipo() const
{
    return OBSTACULO;
}
