#ifndef RIVAL_H
#define RIVAL_H

#include "personaje.h"

class Rival : public Personaje
{
private:

    Vector2D posicionDisco;
    Vector2D posicionJugador;

    double distanciaDisco;

    bool debeAtacar;

    int ataquesExitosos;
    int ataquesFallidos;

public:

    Rival();
    ~Rival();
    Rival(const Vector2D &posicion,double radio,double velocidadMaxima,double aceleracion,double fuerzaDisparo,double alcanceGolpe);

    void actualizar(double dt) override;

    void percibir(const Disco &disco,const Personaje &jugador);

    void razonar();

    void actuar(Disco &disco, double dt);

    void aprender();

    bool getDebeAtacar() const;
    TipoEntidad getTipo() const override;
};

#endif
