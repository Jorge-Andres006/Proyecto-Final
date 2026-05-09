#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>

#include "disco.h"
#include "entidad.h"

class Jugador : public Entidad {
private:
    std::string nombre;

    int puntuacion;

    double velocidadMaxima;

    double aceleracion;

    double fuerzaDisparo;

    double alcanceGolpe;

public:
    static constexpr double VELOCIDAD_MAXIMA_BASE = 10.0;

    static constexpr double ACELERACION_BASE = 5.0;

    static constexpr double FUERZA_DISPARO_BASE = 20.0;

    static constexpr double ALCANCE_GOLPE_BASE = 8.0;

    Jugador();

    Jugador(const std::string &nombre, const Vector2D &posicion, double radio,
            double velocidadMaxima, double aceleracion, double fuerzaDisparo,
            double alcanceGolpe);

    void actualizar(double dt) override;

    void moverEnDireccion(const Vector2D &direccion, double dt);

    void frenar();

    void limitarVelocidad();

    void disparar(Disco &disco, const Vector2D &direccion);

    bool puedeGolpear(const Disco &disco) const;

    void sumarPunto();

    std::string getNombre() const;

    int getPuntuacion() const;

    double getVelocidadMaxima() const;

    double getAceleracion() const;

    double getFuerzaDisparo() const;

    double getAlcanceGolpe() const;

    void setNombre(const std::string &nombre);

    void setVelocidadMaxima(double velocidadMaxima);

    void setAceleracion(double aceleracion);

    void setFuerzaDisparo(double fuerzaDisparo);

    void setAlcanceGolpe(double alcanceGolpe);
};

#endif
