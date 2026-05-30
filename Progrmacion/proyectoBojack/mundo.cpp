#include "mundo.h"

using namespace std;

Mundo::Mundo(double ancho, double alto)
{
    this->ancho = ancho;
    this->alto = alto;
}

void Mundo::agregarEntidad(Entidad *entidad)
{
    entidades.push_back(entidad);
}

void Mundo::actualizar(double dt)
{
    actualizarEntidades(dt);

    manejarColisiones();

    manejarLimites();
}

void Mundo::actualizarEntidades(double dt)
{
    for (Entidad *entidad : entidades)
    {
        entidad->actualizar(dt);
    }
}

void Mundo::manejarColisiones()
{
    for (size_t i = 0; i < entidades.size(); i++)
    {
        for (size_t j = i + 1; j < entidades.size(); j++)
        {
            Entidad *a = entidades[i];

            Entidad *b = entidades[j];

            if (a->colisionaCon(*b))
            {
                if (a->getTipo() == OBSTACULO ||
                    b->getTipo() == OBSTACULO)
                {
                    continue;
                }

                Vector2D velocidadA = a->getVelocidad();

                Vector2D velocidadB = b->getVelocidad();

                a->setVelocidad(-velocidadA);

                b->setVelocidad(-velocidadB);
            }
        }
    }
}

void Mundo::manejarLimites()
{
    for (Entidad *entidad : entidades)
    {
        if(entidad->getTipo() == OBSTACULO)
        {
            continue;
        }

        Vector2D posicion = entidad->getPosicion();

        Vector2D velocidad = entidad->getVelocidad();

        double radio = entidad->getRadio();

        if (posicion.getX() - radio < 0)
        {
            posicion.setX(radio);

            velocidad.setX(-velocidad.getX());
        }

        if (posicion.getX() + radio > ancho)
        {
            posicion.setX(ancho - radio);

            velocidad.setX(-velocidad.getX());
        }


        if (posicion.getY() - radio < 0)
        {
            posicion.setY(radio);

            velocidad.setY(-velocidad.getY());
        }

        if (posicion.getY() + radio > alto)
        {
            posicion.setY(alto - radio);

            velocidad.setY(-velocidad.getY());
        }

        entidad->setPosicion(posicion);

        entidad->setVelocidad(velocidad);
    }
}

void Mundo::eliminarEntidad(Entidad *entidad)
{
    for(size_t i = 0; i < entidades.size(); i++)
    {
        if(entidades[i] == entidad)
        {
            entidades.erase(
                entidades.begin() + i
                );

            return;
        }
    }
}

