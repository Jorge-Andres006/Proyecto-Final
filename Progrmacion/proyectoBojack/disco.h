#ifndef DISCO_H
#define DISCO_H

#include "entidad.h"

class Disco : public Entidad {
private:
    double masa;

    double friccion;

    double rebote;

    double velocidadMaxima;

public:
    static constexpr double FRICCION_BASE = 0.98;
    static constexpr double REBOTE_BASE = 0.8;
    static constexpr double MASA_BASE = 1.0;
    static constexpr double VELOCIDAD_MAXIMA_BASE = 30.0;

    Disco();
    ~Disco();
    Disco(const Vector2D &posicion, const Vector2D &velocidad, double radio,
          double masa, double friccion, double rebote, double velocidadMaxima);

    void actualizar(double dt) override;

    void aplicarFriccion(double dt);

    void aplicarImpulso(const Vector2D &impulso);

    void limitarVelocidad();

    void rebotarX();

    void rebotarY();

    double getMasa() const;

    double getFriccion() const;

    double getRebote() const;

    double getVelocidadMaxima() const;

    void setMasa(double masa);

    void setFriccion(double friccion);

    void setRebote(double rebote);

    void setVelocidadMaxima(double velocidadMaxima);
};

#endif
