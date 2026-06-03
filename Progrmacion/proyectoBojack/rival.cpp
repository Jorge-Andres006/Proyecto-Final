#include "rival.h"
#include "qdebug.h"
#include "qlogging.h"

using namespace std;

Rival::Rival() : Personaje() {

    posicionDisco = Vector2D();

    posicionJugador = Vector2D();

    distanciaDisco = 0.0;

    debeAtacar = false;
    tieneDisco = false;

    ataquesExitosos = 0;

    ataquesFallidos = 0;
    direccionEsquive = 1;
}
Rival::~Rival(){

}
Rival::Rival(const Vector2D &posicion,double radio,double velocidadMaxima,double aceleracion,double fuerzaDisparo,double alcanceGolpe): Personaje(posicion,radio,velocidadMaxima,aceleracion,fuerzaDisparo,alcanceGolpe) {

    posicionDisco = Vector2D();

    posicionJugador = Vector2D();

    distanciaDisco = 0.0;

    debeAtacar = false;
    tieneDisco = false;

    ataquesExitosos = 0;

    ataquesFallidos = 0;
    direccionEsquive = 1;
}

void Rival::actualizar(double dt) {

    Personaje::actualizar(dt);
}

void Rival::percibir(const Disco &disco,const Personaje &jugador) {

    posicionDisco = disco.getPosicion();

    posicionJugador = jugador.getPosicion();

    distanciaDisco = posicion.distancia(posicionDisco);
}

void Rival::razonar()
{
    Vector2D centroArcoJugador(
        110,
        315
        );

    double distanciaArco =
        posicion.distancia(
            centroArcoJugador
            );

    if(tieneDisco && distanciaArco < 250)
    {
        if(arcoBloqueado())
        {
            qDebug()
            << "ARCO BLOQUEADO";

            debeAtacar = false;
        }
        else
        {
            qDebug()
            << "TIRO LIBRE";

            debeAtacar = true;
        }
    }
}

void Rival::actuar(Disco &disco)
{
    Vector2D direccion;

    if(tieneDisco)
    {
        direccion =
            Vector2D(
                110,
                315
                ) - posicion;
    }
    else
    {
        direccion =posicionDisco - posicion;
    }
    if(tieneDisco && arcoBloqueado())
    {
        Vector2D direccionArco =
            (
                Vector2D(
                    110,
                    315
                    ) - posicion
                ).normalizar();
        if(posicionJugador.getY() > posicion.getY())
        {
            direccionEsquive = -1;
        }
        else
        {
            direccionEsquive = 1;
        }
        Vector2D movimientoLateral(
            0,
            direccionEsquive
            );

        Vector2D direccionFinal =direccionArco +movimientoLateral;

        direccionFinal =direccionFinal.normalizar();

        Vector2D nuevaPosicion =posicion +direccionFinal * 2.0;
        if(nuevaPosicion.getY() <= 80 + radio)
        {
            nuevaPosicion.setY(
                80 + radio
                );

            direccionEsquive = 1;
        }

        if(nuevaPosicion.getY() >= 600 - radio)
        {
            nuevaPosicion.setY(
                600 - radio
                );

            direccionEsquive = -1;
        }

        setPosicion(
            nuevaPosicion
            );

        return;
    }
    if(debeAtacar)
    {
        Vector2D direccionDisparo =
            Vector2D(
                110,
                315
                ) - posicion;

        disparar(
            disco,
            direccionDisparo
            );


        Vector2D offset =direccionDisparo.normalizar() * 50.0;

        disco.setPosicion(
            posicion + offset
            );
        tieneDisco = false;
        debeAtacar = false;


    }
    else
    {
        Vector2D direccionNormalizada =
            direccion.normalizar() * 1.5;

        double velocidadRival = 1.3;

        if(tieneDisco)
        {
            velocidadRival = 1.4;
        }

        Vector2D nuevaPosicion =posicion +direccionNormalizada *velocidadRival;
        double radioRival = radio;
        if(nuevaPosicion.getX() < 120 + radioRival)
        {
            nuevaPosicion.setX(
                120 + radioRival
                );
        }

        if(nuevaPosicion.getX() > 1150 - radioRival)
        {
            nuevaPosicion.setX(
                1150 - radioRival
                );
        }

        if(nuevaPosicion.getY() < 80 + radioRival)
        {
            nuevaPosicion.setY(
                80 + radioRival
                );
        }

        if(nuevaPosicion.getY() > 600 - radioRival)
        {
            nuevaPosicion.setY(
                600 - radioRival
                );
        }
        double distanciaJugador =nuevaPosicion.distancia(
                posicionJugador
                );

        if(
            distanciaJugador >
            radio * 2
            )
        {
            setPosicion(
                nuevaPosicion
                );
        }
        else
        {
            Vector2D separacion =
                (
                    nuevaPosicion -
                    posicionJugador
                    ).normalizar();

            nuevaPosicion =posicionJugador +separacion *(radio * 2);

            setPosicion(
                nuevaPosicion
                );
        }
    }
}

void Rival::aprender() {

    if (ataquesFallidos > ataquesExitosos) {

        fuerzaDisparo *= 0.99;
    }

    else if (ataquesExitosos > ataquesFallidos) {

        fuerzaDisparo *= 1.01;
    }

    if (fuerzaDisparo < 5.0) {

        fuerzaDisparo = 5.0;
    }

    if (fuerzaDisparo > 40.0) {

        fuerzaDisparo = 40.0;
    }
}

bool Rival::getDebeAtacar() const {

    return debeAtacar;
}
bool Rival::getTieneDisco() const
{
    return tieneDisco;
}

void Rival::setTieneDisco(bool tieneDisco)
{
    this->tieneDisco = tieneDisco;
}
bool Rival::arcoBloqueado() const
{
    Vector2D centroArco(
        110,
        315
        );

    Vector2D direccionTiro =
        centroArco - posicion;

    double distanciaArco =
        direccionTiro.magnitud();

    Vector2D direccionNormalizada =
        direccionTiro.normalizar();

    Vector2D direccionJugador =
        posicionJugador - posicion;

    double proyeccion =
        direccionJugador.getX() *
            direccionNormalizada.getX()
        +
        direccionJugador.getY() *
            direccionNormalizada.getY();

    if(
        proyeccion < 0 ||
        proyeccion > distanciaArco
        )
    {
        return false;
    }

    Vector2D puntoMasCercano =
        posicion +
        direccionNormalizada *
            proyeccion;

    double distanciaJugadorLinea =
        puntoMasCercano.distancia(
            posicionJugador
            );

    return distanciaJugadorLinea < 40.0;
}
TipoEntidad Rival::getTipo() const
{
    return RIVAL;
}
