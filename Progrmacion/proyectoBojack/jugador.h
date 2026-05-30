#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>

#include "personaje.h"

class Jugador : public Personaje {

private:

    std::string nombre;

    int puntuacion;

public:

    Jugador();
    ~Jugador();
    Jugador(const std::string &nombre,const Vector2D &posicion,double radio,double velocidadMaxima,double aceleracion,double fuerzaDisparo,double alcanceGolpe);

    void actualizar(double dt) override;

    void sumarPunto();

    std::string getNombre() const;

    int getPuntuacion() const;
    TipoEntidad getTipo() const override;

    void setNombre(const std::string &nombre);
};

#endif
