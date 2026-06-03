#include "rival.h"
#include <cmath>


using namespace std;

Rival::Rival() : Personaje() {

    posicionDisco = Vector2D();

    posicionJugador = Vector2D();

    distanciaDisco = 0.0;

    debeAtacar = false;
    tieneDisco = false;
    jugadorTieneDisco = false;
    debeRobar = false;
    acabaDeDisparar = false;
    ataquesExitosos = 0;

    ataquesFallidos = 0;
    direccionEsquive = 1;

    tiempoIntentoRobo = 0.0;

}
Rival::~Rival(){

}
Rival::Rival(const Vector2D &posicion,double radio,double velocidadMaxima,double aceleracion,double fuerzaDisparo,double alcanceGolpe): Personaje(posicion,radio,velocidadMaxima,aceleracion,fuerzaDisparo,alcanceGolpe) {

    posicionDisco = Vector2D();

    posicionJugador = Vector2D();

    distanciaDisco = 0.0;

    debeAtacar = false;
    tieneDisco = false;
    jugadorTieneDisco = false;
    debeRobar = false;
    acabaDeDisparar = false;

    ataquesExitosos = 0;

    ataquesFallidos = 0;
    direccionEsquive = 1;
    tiempoIntentoRobo = 0.0;

}

void Rival::actualizar(double dt)
{
    Personaje::actualizar(dt);

    if(tiempoIntentoRobo > 0.0)
    {
        tiempoIntentoRobo -= dt;
    }

}

void Rival::percibir(const Disco &disco,const Personaje &jugador,bool jugadorTieneDisco) {

    posicionDisco = disco.getPosicion();

    posicionJugador = jugador.getPosicion();

    distanciaDisco = posicion.distancia(posicionDisco);
    this->jugadorTieneDisco =jugadorTieneDisco;
}

void Rival::razonar()
{
    debeRobar = false;
    if(jugadorTieneDisco &&puedeIntentarRobo())
    {
        double distanciaJugador =posicion.distancia(
                posicionJugador
                );

        if(distanciaJugador <=40)
        {

            debeRobar = true;
        }
    }
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
        if(arcoBloqueado()||obstaculoBloqueaDisparo()
            )
        {
            debeAtacar = false;
        }
        else
        {
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
    else if(jugadorTieneDisco)
    {
        Vector2D centroArco(
            1170,
            315
            );

        double xJugador =posicionJugador.getX();

        if(xJugador < 635)
        {
            direccion =posicionJugador -posicion;
        }
        else if(xJugador > 950)
        {
            direccion =posicionJugador -posicion;
        }
        else
        {
            Vector2D direccionArco =
                (
                    centroArco -
                    posicionJugador
                    ).normalizar();

            Vector2D puntoDefensivo =
                posicionJugador +
                direccionArco * 120;

            direccion =puntoDefensivo -posicion;
        }
    }
    else
    {
        Vector2D posicionFutura =posicionDisco +disco.getVelocidad() * 0.8;

        direccion =posicionFutura - posicion;
    }
    direccionActual =direccion.normalizar();
    if(tieneDisco &&(arcoBloqueado()||obstaculoBloqueaDisparo()))
    {
        Vector2D direccionArco =(
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
        Vector2D direccionDisparo =Vector2D(110,315) - posicion;
        acabaDeDisparar = true;
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
        bool hayColisionObstaculo = false;

        for(const Vector2D& obstaculo :posicionesObstaculos)
        {

            Vector2D puntoColision =nuevaPosicion +Vector2D(0,30);

            if(
                puntoColision.distancia(
                    obstaculo
                    ) < 35
                )
            {
                hayColisionObstaculo = true;

                break;
            }
        }
        if(hayColisionObstaculo)
        {
            Vector2D esquive(
                -direccionNormalizada.getY(),
                direccionNormalizada.getX()
                );

            setPosicion(
                posicion +
                esquive * velocidadRival
                );

            return;
        }

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
                (nuevaPosicion -posicionJugador).normalizar();

            nuevaPosicion =posicionJugador +separacion * (radio * 2);

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
bool Rival::puedeIntentarRobo() const
{
    return tiempoIntentoRobo <= 0.0;
}
bool Rival::getDebeRobar() const
{
    return debeRobar;
}
void Rival::setTiempoIntentoRobo(
    double tiempo
    )
{
    tiempoIntentoRobo = tiempo;
}
Vector2D Rival::getDireccionActual() const
{
    return direccionActual;
}
bool Rival::getAcabaDeDisparar() const
{
    return acabaDeDisparar;
}
void Rival::setAcabaDeDisparar(bool valor)
{
    acabaDeDisparar = valor;
}
void Rival::setPosicionesObstaculos(
    const std::vector<Vector2D>& posiciones
    )
{
    posicionesObstaculos = posiciones;
}
bool Rival::obstaculoBloqueaDisparo()
{
    Vector2D arco(
        110,
        315
        );

    for(const Vector2D& obstaculo :
         posicionesObstaculos)
    {
        double distanciaLinea =
            fabs(
                (arco.getY() - posicion.getY()) *
                    obstaculo.getX()
                -
                (arco.getX() - posicion.getX()) *
                    obstaculo.getY()
                +
                arco.getX() * posicion.getY()
                -
                arco.getY() * posicion.getX()
                )
            /
            sqrt(
                pow(
                    arco.getY() -
                        posicion.getY(),
                    2
                    )
                +
                pow(
                    arco.getX() -
                        posicion.getX(),
                    2
                    )
                );

        if(distanciaLinea < 40)
        {
            return true;
        }
    }

    return false;
}
TipoEntidad Rival::getTipo() const
{
    return RIVAL;
}
