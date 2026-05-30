#include "nivelEntrenamiento.h"

using namespace std;

NivelEntrenamiento::NivelEntrenamiento(
    double ancho,
    double alto,
    QGraphicsScene *scene
    )
    : Nivel(ancho, alto),

    jugador(
        "Bojack",
        Vector2D(
            100.0,
            alto / 2.0
            ),
        20.0,
        10.0,
        5.0,
        20.0,
        10.0
        ),

    disco(
        Vector2D(
            ancho / 2.0,
            alto / 2.0
            ),
        Vector2D(0.0, 0.0),
        10.0,
        1.0,
        0.995,
        0.8,
        500.0
        ),

    arco(
        Vector2D(
            ancho - 120.0,
            alto / 2.0 - 100.0
            ),
        80.0,
        200.0
        )
{
    this->scene = scene;

    itemJugador = nullptr;

    itemDisco = nullptr;

    itemArco = nullptr;

    goles = 0;

    tiempoSpawnObstaculos = 0.0;

    potencia = 0.0;
    tiempoRecogerDisco = 0.0;


    cargandoDisparo = false;
    tieneDisco = false;
    invulnerable = false;

    tiempoInvulnerabilidad = 0.0;
    direccionJugador = Vector2D(1,0);
}

NivelEntrenamiento::~NivelEntrenamiento()
{

    for(Obstaculo* obstaculo : obstaculos)
    {
        delete obstaculo;
    }
}

void NivelEntrenamiento::iniciar()
{
    mundo.agregarEntidad(&disco);
    mundo.agregarEntidad(&jugador);

    Obstaculo* obstaculo =
        new Obstaculo(
            Vector2D(
                1100,
                300
                ),
            20.0
            );

    obstaculos.push_back(
        obstaculo
        );
    QGraphicsEllipseItem* itemObstaculo =
        scene->addEllipse(
            obstaculo->getPosicion().getX() - 20,
            obstaculo->getPosicion().getY() - 20,
            40,
            40,
            QPen(Qt::black),
            QBrush(Qt::darkRed)
            );

    itemsObstaculos.push_back(
        itemObstaculo
        );
    mundo.agregarEntidad(
        obstaculo
        );

    obstaculo->setVelocidad(
        Vector2D(
            -100,
            0
            )
        );

    itemJugador =scene->addEllipse(
            jugador.getPosicion().getX() - 20,
            jugador.getPosicion().getY() - 20,
            40,
            40,
            QPen(Qt::black),
            QBrush(Qt::blue)
            );

    itemDisco =scene->addEllipse(
            disco.getPosicion().getX() - 10,
            disco.getPosicion().getY() - 10,
            20,
            20,
            QPen(Qt::black),
            QBrush(Qt::red)
            );

    itemArco =scene->addRect(
            arco.getPosicion().getX(),
            arco.getPosicion().getY(),
            arco.getAncho(),
            arco.getAlto(),
            QPen(Qt::green, 3),
            QBrush(Qt::NoBrush)
            );
}

void NivelEntrenamiento::actualizar(double dt)
{
    tiempo += dt;
    if(tiempoRecogerDisco > 0.0)
    {
        tiempoRecogerDisco -= dt;
    }
    if(invulnerable)
    {
        tiempoInvulnerabilidad -= dt;

        if(tiempoInvulnerabilidad <= 0.0)
        {
            invulnerable = false;

            tiempoInvulnerabilidad = 0.0;
        }
    }
    tiempoSpawnObstaculos += dt;
    if(tiempoSpawnObstaculos >= 2.0)
    {
        generarObstaculo();

        tiempoSpawnObstaculos = 0.0;
    }

    if(cargandoDisparo)
    {
        if(potencia < 300.0)
        {
            potencia += 200.0 * dt;

            if(potencia > 300.0)
            {
                potencia = 300.0;
            }
        }
    }

    mundo.actualizar(dt);
    for(Obstaculo* obstaculo : obstaculos)
    {
        if(jugador.colisionaCon(*obstaculo))
        {
            if(tieneDisco && !invulnerable)
            {
                tieneDisco = false;

                disco.setPosicion(
                    Vector2D(
                        640,
                        360
                        )
                    );

                disco.setVelocidad(
                    Vector2D(
                        0,
                        0
                        )
                    );

                invulnerable = true;

                tiempoInvulnerabilidad = 2.0;
            }
        }
    }
    for(Obstaculo* obstaculo : obstaculos)
    {
        if(disco.colisionaCon(*obstaculo))
        {

            Vector2D velocidad =disco.getVelocidad();

            disco.setVelocidad(
                velocidad * -0.7
                );
        }
    }
    if(!tieneDisco && tiempoRecogerDisco <= 0.0)
    {
        if(
            jugador.getPosicion().distancia(
                disco.getPosicion()
                ) < 20.0
            )
        {
            tieneDisco = true;
        }
    }

    if(tieneDisco)
    {
        disco.setPosicion(
            jugador.getPosicion() +
            direccionJugador * 35.0
            );

        disco.setVelocidad(
            Vector2D(0,0)
            );
    }

    if(itemJugador)
    {
        itemJugador->setRect(
            jugador.getPosicion().getX() - 20,
            jugador.getPosicion().getY() - 20,
            40,
            40
            );
    }

    if(itemDisco)
    {
        itemDisco->setRect(
            disco.getPosicion().getX() - 10,
            disco.getPosicion().getY() - 10,
            20,
            20
            );
    }
    for(size_t i = 0;i < obstaculos.size();i++)
    {
        itemsObstaculos[i]->setRect(
            obstaculos[i]->getPosicion().getX() - 20,
            obstaculos[i]->getPosicion().getY() - 20,
            40,
            40
            );
    }
    for(size_t i = 0; i < obstaculos.size(); )
    {
        if(obstaculos[i]->getPosicion().getX() < -50)
        {
            mundo.eliminarEntidad(
                obstaculos[i]
                );

            scene->removeItem(
                itemsObstaculos[i]
                );

            delete itemsObstaculos[i];

            delete obstaculos[i];

            itemsObstaculos.erase(
                itemsObstaculos.begin() + i
                );

            obstaculos.erase(
                obstaculos.begin() + i
                );
        }
        else
        {
            i++;
        }
    }
    verificarGol();
}

void NivelEntrenamiento::finalizar()
{
    terminado = true;
}

void NivelEntrenamiento::verificarGol()
{
    if(arco.detectarGol(disco))
    {
        goles++;

        disco.setPosicion(
            Vector2D(
                50.0,
                50.0
                )
            );

        disco.setVelocidad(
            Vector2D(
                0.0,
                0.0
                )
            );
    }
}

void NivelEntrenamiento::generarObstaculo()
{
    double x = 1280;

    double y = 100 + (rand() % 500);

    Obstaculo* obstaculo =
        new Obstaculo(
            Vector2D(x, y),
            20.0
            );

    obstaculo->setVelocidad(
        Vector2D(
            -100,
            0
            )
        );

    obstaculos.push_back(
        obstaculo
        );

    mundo.agregarEntidad(
        obstaculo
        );

    QGraphicsEllipseItem* itemObstaculo =
        scene->addEllipse(
            x - 20,
            y - 20,
            40,
            40,
            QPen(Qt::black),
            QBrush(Qt::darkRed)
            );

    itemsObstaculos.push_back(
        itemObstaculo
        );
}

Jugador& NivelEntrenamiento::getJugador()
{
    return jugador;
}

Disco& NivelEntrenamiento::getDisco()
{
    return disco;
}


void NivelEntrenamiento::iniciarCarga()
{
    cargandoDisparo = true;
}

void NivelEntrenamiento::detenerCarga()
{
    if(!tieneDisco)
    {
        return;
    }

    cargandoDisparo = false;

    tieneDisco = false;

    tiempoRecogerDisco = 0.5;

    Vector2D direccion = direccionJugador;

    if(potencia < 10.0)
    {
        potencia = 10.0;
    }

    disco.setVelocidad(
        direccion * (potencia * 10)
        );

    potencia = 0.0;
}


double NivelEntrenamiento::getPotencia() const
{
    return potencia;
}
void NivelEntrenamiento::moverJugador(
    const Vector2D& direccion
    )
{
    if(direccion.getX() != 0 || direccion.getY() != 0)
    {
        direccionJugador =direccion.normalizar();
    }
    Vector2D nuevaPosicion =jugador.getPosicion() +direccion;

    double radio =
        jugador.getRadio();

    if(
        nuevaPosicion.getX()
        <
        LIMITE_IZQUIERDO + radio
        )
    {
        nuevaPosicion.setX(
            LIMITE_IZQUIERDO + radio
            );
    }

    if(
        nuevaPosicion.getX()
        >
        LIMITE_DERECHO - radio
        )
    {
        nuevaPosicion.setX(
            LIMITE_DERECHO - radio
            );
    }

    if(
        nuevaPosicion.getY()
        <
        LIMITE_SUPERIOR + radio
        )
    {
        nuevaPosicion.setY(
            LIMITE_SUPERIOR + radio
            );
    }

    if(
        nuevaPosicion.getY()
        >
        LIMITE_INFERIOR - radio
        )
    {
        nuevaPosicion.setY(
            LIMITE_INFERIOR - radio
            );
    }

    jugador.setPosicion(
        nuevaPosicion
        );
}
