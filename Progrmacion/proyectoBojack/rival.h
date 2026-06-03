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
    bool jugadorTieneDisco;
    int ataquesExitosos;
    int ataquesFallidos;
    bool tieneDisco;
    int direccionEsquive;
    double tiempoIntentoRobo;
    bool debeRobar;

public:

    Rival();
    ~Rival();
    Rival(const Vector2D &posicion,double radio,double velocidadMaxima,double aceleracion,double fuerzaDisparo,double alcanceGolpe);

    void actualizar(double dt) override;

    void percibir(const Disco &disco, const Personaje &jugador,bool jugadorTieneDisco);

    void razonar();

    void actuar(Disco &disco);

    void aprender();

    bool getDebeAtacar() const;
    TipoEntidad getTipo() const override;
    bool getTieneDisco() const;

    void setTieneDisco(bool tieneDisco);
    bool arcoBloqueado() const;
    bool puedeIntentarRobo() const;
    bool getDebeRobar() const;
    void setTiempoIntentoRobo(double tiempo);
};

#endif
