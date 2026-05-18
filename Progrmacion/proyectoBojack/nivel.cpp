#include "nivel.h"

using namespace std;

Nivel::Nivel(double ancho, double alto)
    : mundo(ancho, alto) {

    tiempo = 0.0;

    terminado = false;
}

Nivel::~Nivel() {}

bool Nivel::estaTerminado() const {

    return terminado;
}

double Nivel::getTiempo() const {

    return tiempo;
}
