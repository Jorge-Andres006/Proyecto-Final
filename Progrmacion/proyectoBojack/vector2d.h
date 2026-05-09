#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

class Vector2D {
private:
    double x;
    double y;

    static constexpr double EPSILON = 1e-9;

public:
    // Constructores
    Vector2D(double x = 0.0, double y = 0.0);

    // Getters
    double getX() const;
    double getY() const;

    // Setters
    void setX(double x);
    void setY(double y);
    void setXY(double x, double y);

    // Operadores aritméticos
    Vector2D operator+(const Vector2D &otro) const;
    Vector2D operator-(const Vector2D &otro) const;
    Vector2D operator*(double escalar) const;
    Vector2D operator/(double escalar) const;

    // Operador negativo unario
    Vector2D operator-() const;

    // Operadores compuestos
    Vector2D &operator+=(const Vector2D &otro);
    Vector2D &operator-=(const Vector2D &otro);
    Vector2D &operator*=(double escalar);
    Vector2D &operator/=(double escalar);

    // Métodos matemáticos
    double magnitud() const;
    double magnitudCuadrada() const;

    Vector2D normalizar() const;

    double dot(const Vector2D &otro) const;
    double cross(const Vector2D &otro) const;

    double distancia(const Vector2D &otro) const;

    // Limita la magnitud del vector
    void limitar(double maximo);

    // Sobrecarga de salida
    friend std::ostream &operator<<(std::ostream &os, const Vector2D &v);
};

#endif
