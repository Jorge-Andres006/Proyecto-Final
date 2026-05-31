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
            630,
            308
            ),
        Vector2D(0.0, 0.0),
        10.0,
        1.0,
        0.995,
        0.8,
        1000.0
        ),

    arco(
        Vector2D(
            ancho - 90,
            alto / 2.0 - 109
            ),
        10,
        120.0
        )
{
    spriteSheet = QPixmap(
        ":/new/prefix1/Imagenes/Sprites.png"
        );
    spriteSheetDisco = QPixmap(
        ":/new/prefix1/Imagenes/spritesDiscoSinFondo.png"
        );
    qDebug() << spriteSheetDisco.isNull();
    this->scene = scene;

    itemJugador = nullptr;

    itemDisco = nullptr;

    itemArco = nullptr;

    hudPotencia = nullptr;

    barraPotencia = nullptr;
    goles = 0;

    tiempoSpawnObstaculos = 0.0;

    potencia = 0.0;
    tiempoRecogerDisco = 0.0;
    frameActual = 0;

    tiempoAnimacion = 0.0;


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

    QPixmap spriteJugador =
        spriteSheet.copy(
            0,      // x
            0,      // y
            135,    // ancho
            147     // alto
            );
    itemJugador =
        scene->addPixmap(
            spriteJugador
            );
    itemJugador->setScale(0.6);
    itemJugador->setPos(
        jugador.getPosicion().getX() - 25,
        jugador.getPosicion().getY() - 25
        );
    discoVertical =
        spriteSheetDisco.copy(
            120,
            0,
            110,
            110
            );

    discoHorizontal =
        spriteSheetDisco.copy(
            120,
            117,
            110,
            110
            );

    itemDisco =
        scene->addPixmap(
            discoVertical
            );
    itemDisco->setScale(0.4);

    itemArco = scene->addRect(
        arco.getPosicion().getX(),
        arco.getPosicion().getY(),
        arco.getAncho(),
        arco.getAlto(),
        Qt::NoPen,
        Qt::NoBrush
        );

    QPixmap marcoGoles(":/new/prefix1/Imagenes/MarcoGoles.png");

    hudGolesItem =scene->addPixmap(marcoGoles);

    hudGolesItem->setPos(
        500,
        10
        );

    hudGolesItem->setScale(0.15);
    QPixmap hud(":/new/prefix1/Imagenes/BarraDePotencia.png");

    hudPotencia = scene->addPixmap(hud);

    hudPotencia->setPos(950, 540);
    hudPotencia->setScale(0.2);
    hudPotencia->setZValue(100);

    barraPotencia =scene->addRect(
            1000,
            617,
            0,
            61,
            QPen(Qt::black),
            QBrush(Qt::green)
            );
}

void NivelEntrenamiento::actualizar(double dt)
{
    tiempoAnimacion += dt;
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
    if(tiempoSpawnObstaculos >= 1)
    {
        generarObstaculo();

        tiempoSpawnObstaculos = 0.0;
    }

    if(cargandoDisparo && tieneDisco)
    {
        if(potencia < 1000.0)
        {
            potencia += 70 * dt;

            if(potencia > 1000.0)
            {
                potencia = 1000.0;
            }
        }
    }
    if(barraPotencia)
    {
        double porcentaje = potencia / 200.0;

        double anchoBarra = potencia;
        if(anchoBarra > 200)
        {
            anchoBarra = 200;
        }
        barraPotencia->setRect(
            1000,
            617,
            anchoBarra,
            61
            );

        if(porcentaje < 0.33)
        {
            barraPotencia->setBrush(Qt::green);
        }
        else if(porcentaje < 0.66)
        {
            barraPotencia->setBrush(Qt::yellow);
        }
        else
        {
            barraPotencia->setBrush(Qt::red);
        }
    }
    mundo.actualizar(dt);
    Vector2D posDisco = disco.getPosicion();

    double limiteDetrasArco =
        arco.getPosicion().getX() +
        arco.getAncho() +
        30;

    if(posDisco.getX() > limiteDetrasArco)
    {
        disco.setPosicion(
            Vector2D(
                630,
                308
                )
            );

        disco.setVelocidad(
            Vector2D(
                0,
                0
                )
            );

        tieneDisco = false;

        potencia = 0.0;

        cargandoDisparo = false;

        tiempoRecogerDisco = 0.5;
    }
    for(Obstaculo* obstaculo : obstaculos)
    {
        Vector2D puntoColision =
            jugador.getPosicion() +
            Vector2D(0, 30);

        if(
            puntoColision.distancia(
                obstaculo->getPosicion()
                ) < 30.0
            )
        {
            if(tieneDisco && !invulnerable)
            {
                tieneDisco = false;

                potencia = 0.0;

                cargandoDisparo = false;

                disco.setPosicion(
                    Vector2D(
                        630,
                        308
                        )
                    );

                disco.setVelocidad(
                    Vector2D(0,0)
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
        Vector2D puntoRecogida =
            jugador.getPosicion() +
            Vector2D(0, 30);

        if(
            puntoRecogida.distancia(
                disco.getPosicion()
                ) < 35.0
            )
        {
            tieneDisco = true;
        }
    }

    if(tieneDisco)
    {
        Vector2D offset =
            direccionJugador * 35.0 +
            Vector2D(0,30);
        if(
            abs(direccionJugador.getX()) >
            abs(direccionJugador.getY())
            )
        {
            itemDisco->setPixmap(
                discoHorizontal
                );
        }
        else
        {
            itemDisco->setPixmap(
                discoVertical
                );
        }
        disco.setPosicion(
            jugador.getPosicion() + offset
            );

        disco.setVelocidad(
            Vector2D(0,0)
            );
    }

    if(itemJugador)
    {
        itemJugador->setPos(
            jugador.getPosicion().getX() - 25,
            jugador.getPosicion().getY() - 25
            );
    }

    if(itemDisco)
    {
        itemDisco->setPos(
            disco.getPosicion().getX() - 18,
            disco.getPosicion().getY() - 18
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
        tieneDisco = false;

        potencia = 0.0;

        cargandoDisparo = false;

        disco.setPosicion(
            Vector2D(
                630,
                308
                )
            );

        disco.setVelocidad(
            Vector2D(
                0,
                0
                )
            );

        tiempoRecogerDisco = 0.5;
        if(goles >= 7)
        {
            qDebug() << "Nivel completado";
            finalizar();
        }

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
    if(!tieneDisco)
    {
        return;
    }

    cargandoDisparo = true;
    potencia = 0.0;
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

    if(potencia < 20.0)
    {
        potencia = 20.0;
    }
    disco.setVelocidad(
        direccion * (potencia * 5)
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
        direccionJugador = direccion.normalizar();
        if(tiempoAnimacion > 0.15)
        {
            frameActual++;

            if(frameActual >= 8)
            {
                frameActual = 0;
            }

            tiempoAnimacion = 0.0;
        }
        if(direccion.getY() > 0)
        {
            itemJugador->setPixmap(
                spriteSheet.copy(
                    frameActual * 135,
                    0,
                    125,
                    135
                    )
                );
        }
        else if(direccion.getY() < 0)
        {
            itemJugador->setPixmap(
                spriteSheet.copy(
                    frameActual * 135,
                    147,
                    125,
                    135
                    )
                );
        }
        else if(direccion.getX() > 0)
        {
            itemJugador->setPixmap(
                spriteSheet.copy(
                    frameActual * 135,
                    294,
                    125,
                    135
                    )
                );
        }
        else if(direccion.getX() < 0)
        {
            itemJugador->setPixmap(
                spriteSheet.copy(
                    frameActual * 135,
                    441,
                    125,
                    135
                    )
                );
        }
    }
    double velocidadJugador = 1.2;

    if(tieneDisco)
    {
        velocidadJugador =0.6;
    }

    Vector2D nuevaPosicion =
        jugador.getPosicion() +
        direccion * velocidadJugador;

    double radio = jugador.getRadio();

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
int NivelEntrenamiento::getGoles() const
{
    return goles;
}
