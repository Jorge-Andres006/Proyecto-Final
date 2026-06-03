#include "nivelenfrentamiento.h"
#include <cmath>
using namespace std;

NivelEnfrentamiento::NivelEnfrentamiento(
    double ancho,
    double alto,
    QGraphicsScene* scene
    )
    : Nivel(ancho,alto),

    jugador(
        "Bojack",
        Vector2D(
            100.0,
            alto/2.0
            ),
        20.0,
        10.0,
        5.0,
        20.0,
        10.0
        ),

    rival(
        Vector2D(
            1100.0,
            alto/2.0
            ),
        20,
        20,
        5.0,
        500.0,
        10.0
        ),

    disco(
        Vector2D(
            645,
            312
            ),
        Vector2D(
            0,
            0
            ),
        10.0,
        1.0,
        0.995,
        0.8,
        1000.0
        ),

    arcoJugador(
        Vector2D(
            110,
            265
            ),
        10,
        100
        ),

    arcoRival(
        Vector2D(
            1170,
            265
            ),
        10,
        100
        )
{
    this->scene = scene;

    spriteSheet =QPixmap(
            ":/new/prefix1/Imagenes/Sprites.png"
            );
    spriteSheetRival =
        QPixmap(
            ":/new/prefix1/Imagenes/mr.penuatButter.png"
            );
    spriteSheetDisparo =QPixmap(
            ":/new/prefix1/Imagenes/SpriteDisparoBojackH.png"
            );

    spriteSheetDisco =QPixmap(
            ":/new/prefix1/Imagenes/spritesDiscoSinFondo.png"
            );
    spriteSheetObstaculos = QPixmap(
        ":/new/prefix1/Imagenes/Obstaculos.png"
        );

    itemJugador = nullptr;
    itemRival = nullptr;

    itemDisco = nullptr;

    hudPotencia = nullptr;
    barraPotencia = nullptr;

    itemArcoJugador = nullptr;
    itemArcoRival = nullptr;

    textoCronometro = nullptr;

    golesJugador = 0;
    golesRival = 0;
    potencia = 0.0;
    tiempoRecogerDisco = 0.0;
    frameActual = 0;
    frameRival = 0;
    tiempoAnimacion = 0.0;
    tiempoAnimacionRival = 0.0;
    frameDisparo = 0;
    tiempoDisparo = 0.0;
    potenciaDisparo = 0.0;
    tiempoProyectil = 0.0;
    velocidadInicialProyectil = 0.0;
    tiempoDisparoRival = 0.0;
    tiempoObstaculos = 0.0;
    posicionInicialProyectil =
        Vector2D(
            0,
            0
            );

    direccionDisparo =
        Vector2D(
            1,
            0
            );

    direccionJugador =
        Vector2D(
            1,
            0
            );

    disparando = false;

    disparoPendiente = false;

    cargandoDisparo = false;

    tieneDisco = false;
    disparoParabolico = false;
    proyectilActivo = false;
    rivalDisparando = false;
}
NivelEnfrentamiento::~NivelEnfrentamiento()
{


}
void NivelEnfrentamiento::iniciar()
{
    mundo.agregarEntidad(
        &jugador
        );

    mundo.agregarEntidad(
        &rival
        );

    mundo.agregarEntidad(
        &disco
        );

    itemJugador =scene->addPixmap(
            spriteSheet.copy(
                0,
                0,
                135,
                147
                )
            );
    itemRival =
        scene->addPixmap(
            spriteSheetRival.copy(
                0,
                0,
                135,
                147
                )
            );

    itemJugador->setScale(
        0.6
        );
    itemRival->setScale(
        0.6
        );
    discoVertical =spriteSheetDisco.copy(
            120,
            0,
            110,
            110
            );

    discoHorizontal =spriteSheetDisco.copy(
            120,
            117,
            110,
            110
            );

    itemDisco =scene->addPixmap(
            discoVertical
            );

    itemDisco->setScale(0.4);

    itemArcoJugador =scene->addRect(
            arcoJugador.getPosicion().getX(),
            arcoJugador.getPosicion().getY(),
            arcoJugador.getAncho(),
            arcoJugador.getAlto(),
            QPen(Qt::NoPen),
            QBrush(Qt::NoBrush)
            );


    itemArcoRival =scene->addRect(
            arcoRival.getPosicion().getX(),
            arcoRival.getPosicion().getY(),
            arcoRival.getAncho(),
            arcoRival.getAlto(),
            QPen(Qt::NoPen),
            QBrush(Qt::NoBrush)
            );

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
    textoCronometro =
        scene->addText("04:00");

    textoCronometro->setDefaultTextColor(
        Qt::white
        );

    textoCronometro->setPos(
        1100,
        20
        );

    textoCronometro->setScale(
        2.0
        );

    textoCronometro->setZValue(
        100
        );
    generarObstaculos();
}
void NivelEnfrentamiento::actualizar(double dt)
{
    tiempo += dt;
    double tiempoRestante =240 - tiempo;

    if(tiempoRestante < 0)
    {
        tiempoRestante = 0;
    }

    int minutos =static_cast<int>(
            tiempoRestante
            ) / 60;

    int segundos =static_cast<int>(
            tiempoRestante
            ) % 60;
    QString textoTiempo =
        QString("%1:%2")
            .arg(
                minutos,
                2,
                10,
                QChar('0')
                )
            .arg(
                segundos,
                2,
                10,
                QChar('0')
                );

    textoCronometro->setPlainText(
        textoTiempo
        );
    if(tiempo >= 240)
    {
        terminado = true;

    }
    tiempoObstaculos += dt;

    if(tiempoObstaculos >= 10.0)
    {
        generarObstaculos();

        tiempoObstaculos = 0.0;
    }
    tiempoAnimacion += dt;
    tiempoAnimacionRival += dt;
    actualizarDisparo(dt);

    if(tiempoRecogerDisco > 0.0)
    {
        tiempoRecogerDisco -= dt;
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
    rival.percibir(
        disco,jugador, tieneDisco
        );

    rival.razonar();
    if(
        rival.getDebeRobar() &&
        tieneDisco
        )
    {
        tieneDisco = false;

        rival.setTieneDisco(true);

        tiempoRecogerDisco = 0.5;

        rival.setTiempoIntentoRobo(1.5);
    }
    rival.setPosicionesObstaculos(
        posicionesObstaculos
        );
    rival.actuar(disco);

    mundo.actualizar(dt);
    for(const Vector2D& obstaculo :
         posicionesObstaculos)
    {
        if(
            disco.getPosicion().distancia(
                obstaculo
                ) < 35
            )
        {
            Vector2D direccionSalida =
                (
                    disco.getPosicion() -
                    obstaculo
                    ).normalizar();

            disco.setPosicion(
                obstaculo +
                direccionSalida * 40
                );

            Vector2D velocidad =
                disco.getVelocidad();

            double temp =
                velocidad.getX();

            velocidad.setX(
                -velocidad.getY()
                );

            velocidad.setY(
                temp
                );

            disco.setVelocidad(
                velocidad * 0.8
                );

            break;
        }
    }
    if(proyectilActivo)
    {
        tiempoProyectil += dt;

        double angulo =ANGULO_PARABOLICO *M_PI /180.0;
        double velocidadHorizontal =velocidadInicialProyectil *cos(angulo);
        double velocidadVertical =velocidadInicialProyectil *sin(angulo);
        double vx;
        if(direccionDisparo.getX() > 0)
        {
            vx = velocidadHorizontal;
        }
        else
        {
            vx = -velocidadHorizontal;
        }
        double vy =-velocidadVertical;
        double x =posicionInicialProyectil.getX() +vx * tiempoProyectil;
        double y =posicionInicialProyectil.getY() +vy * tiempoProyectil +0.5 *GRAVEDAD *tiempoProyectil *tiempoProyectil;
        disco.setPosicion(
            Vector2D(
                x,
                y
                )
            );

        if(y > LIMITE_INFERIOR)
        {
            y = LIMITE_INFERIOR;

            disco.setPosicion(
                Vector2D(
                    x,
                    y
                    )
                );

            proyectilActivo = false;

            disparoParabolico = false;
        }
    }

    Vector2D posDisco =disco.getPosicion();

    double radio =disco.getRadio();

    if(posDisco.getY() - radio < LIMITE_SUPERIOR)
    {
        posDisco.setY(
            LIMITE_SUPERIOR + radio
            );

        disco.setPosicion(
            posDisco
            );

        disco.rebotarY();
    }

    if(posDisco.getY() + radio > LIMITE_INFERIOR)
    {
        posDisco.setY(
            LIMITE_INFERIOR - radio
            );

        disco.setPosicion(
            posDisco
            );

        disco.rebotarY();
    }
    verificarGol();

    double limiteArcoJugador =arcoJugador.getPosicion().getX() - 30;

    double limiteArcoRival =arcoRival.getPosicion().getX() +arcoRival.getAncho() +30;

    if(posDisco.getX() < limiteArcoJugador)
    {
        reiniciarDisco();
    }

    if(posDisco.getX() > limiteArcoRival)
    {
        reiniciarDisco();
    }
    if(!tieneDisco &&!rival.getTieneDisco() &&tiempoRecogerDisco <= 0.0 &&!proyectilActivo)
    {
        if(!tieneDisco &&!rival.getTieneDisco() &&!proyectilActivo
            )
        {
            if(
                rival.getPosicion().distancia(
                    disco.getPosicion()
                    ) < 35.0
                )
            {

                rival.setTieneDisco(true);
            }
        }
        Vector2D puntoRecogida =jugador.getPosicion() +Vector2D(0,30);

        if(
            puntoRecogida.distancia(
                disco.getPosicion()
                ) < 35.0
            )
        {
            tieneDisco = true;
        }
    }
    if(tieneDisco && !disparando)
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
            jugador.getPosicion() +
            offset
            );

        disco.setVelocidad(
            Vector2D(0,0)
            );
    }
    if(rival.getTieneDisco())
    {
        disco.setPosicion(
            rival.getPosicion()
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
    if(rival.getAcabaDeDisparar())
    {
        rivalDisparando = true;

        tiempoDisparoRival = 0.2;
        rival.setAcabaDeDisparar(false);
    }
    if(rivalDisparando)
    {
        tiempoDisparoRival -= dt;

        if(tiempoDisparoRival <= 0.0)
        {
            rivalDisparando = false;
        }
    }
    if(itemRival)
    {
        Vector2D direccionRival =rival.getDireccionActual();

        if(rivalDisparando)
        {
            itemRival->setPixmap(
                spriteSheetRival.copy(
                    7 * 135,
                    441,
                    135,
                    147
                    )
                );
        }
        else
        {

       if(tiempoAnimacionRival > 0.15)
        {
            frameRival++;

            if(frameRival >= 8)
            {
                frameRival = 0;
            }

            tiempoAnimacionRival = 0.0;
        }

       if(
           abs(direccionRival.getX()) >
           abs(direccionRival.getY())
           )
       {
           int frameLateral = frameRival;

           if(frameLateral > 6)
           {
               frameLateral = 0;
           }

           if(direccionRival.getX() > 0)
           {
               itemRival->setPixmap(
                   spriteSheetRival.copy(
                       frameLateral * 135,
                       294,
                       135,
                       147
                       )
                   );
           }
           else
           {
               itemRival->setPixmap(
                   spriteSheetRival.copy(
                       frameLateral * 135,
                       441,
                       135,
                       147
                       )
                   );
           }
       }
       else
       {
           if(direccionRival.getY() > 0)
           {
               itemRival->setPixmap(
                   spriteSheetRival.copy(
                       frameRival * 135,
                       0,
                       135,
                       147
                       )
                   );
           }
           else
           {
               itemRival->setPixmap(
                   spriteSheetRival.copy(
                       frameRival * 135,
                       147,
                       135,
                       147
                       )
                   );
           }
       }
        }
        itemRival->setPos(
            rival.getPosicion().getX() - 25,
            rival.getPosicion().getY() - 25
            );
    }
    if(itemDisco)
    {
        itemDisco->setPos(
            disco.getPosicion().getX() - 18,
            disco.getPosicion().getY() - 18
            );
    }
}
void NivelEnfrentamiento::finalizar()
{
    terminado = true;
}
void NivelEnfrentamiento::iniciarCarga()
{
    if(!tieneDisco)
    {
        return;
    }

    cargandoDisparo = true;
    potencia = 0.0;
}

void NivelEnfrentamiento::detenerCarga()
{
    if(!tieneDisco)
    {
        return;
    }

    cargandoDisparo = false;

    if(potencia < 20.0)
    {
        potencia = 20.0;
    }

    disparando = true;

    disparoPendiente = true;

    frameDisparo = 0;

    tiempoDisparo = 0.0;

    direccionDisparo = direccionJugador;

    potenciaDisparo = potencia;

}

void NivelEnfrentamiento::moverJugador(
    const Vector2D& direccion
    )
{
    if(
        !disparando &&
        (direccion.getX() != 0 || direccion.getY() != 0)
        )
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
    double velocidadJugador = 0.8;

    if(tieneDisco)
    {
        velocidadJugador =0.6;
    }

    Vector2D nuevaPosicion =jugador.getPosicion() +direccion * velocidadJugador;

    double radio = jugador.getRadio();

    if(nuevaPosicion.getX()<LIMITE_IZQUIERDO + radio)
    {
        nuevaPosicion.setX(
            LIMITE_IZQUIERDO + radio
            );
    }

    if(nuevaPosicion.getX()>LIMITE_DERECHO - radio)
    {
        nuevaPosicion.setX(
            LIMITE_DERECHO - radio
            );
    }

    if(nuevaPosicion.getY()<LIMITE_SUPERIOR + radio)
    {
        nuevaPosicion.setY(
            LIMITE_SUPERIOR + radio
            );
    }

    if(nuevaPosicion.getY()>LIMITE_INFERIOR - radio)
    {
        nuevaPosicion.setY(
            LIMITE_INFERIOR - radio
            );
    }

    bool hayColision = false;

    for(const Vector2D& posicionObstaculo :
         posicionesObstaculos)
    {
        Vector2D puntoColision =
            nuevaPosicion +
            Vector2D(0,30);

        if(
            puntoColision.distancia(
                posicionObstaculo
                ) < 35
            )
        {
            hayColision = true;
            break;
        }
    }
    double distanciaRival =nuevaPosicion.distancia(rival.getPosicion());
    if(distanciaRival <jugador.getRadio() +rival.getRadio())
    {
        hayColision = true;
    }
    if(!hayColision)
    {
        jugador.setPosicion(
            nuevaPosicion
            );
    }
}

void NivelEnfrentamiento::actualizarDisparo(
    double dt
    )
{
    if(!disparando)
    {
        return;
    }

    tiempoDisparo += dt;
    int fila = 0;
    int frameReal = frameDisparo;
    int frameMaximo = 8;

    if(direccionJugador.getX() > 0)
    {

        fila = 0;

        int framesDerecha[3] ={4, 5,6};

        if(frameDisparo < 3)
        {
            frameReal = framesDerecha[frameDisparo];
        }

        frameMaximo = 3;
    }
    else if(direccionJugador.getY() < 0)
    {

        fila = 1;
        int framesArriba[3]={6,5,4};
        if(frameDisparo < 3)
        {
            frameReal = framesArriba[frameDisparo];
        }
        frameMaximo = 3;
    }
    else if(direccionJugador.getX() < 0)
    {
        fila = 3;

        int framesIzquierda[3] ={7,6,5};

        if(frameDisparo < 3)
        {
            frameReal = framesIzquierda[frameDisparo];
        }

        frameMaximo = 3;
    }
    else
    {

        fila = 3;

        frameMaximo = 3;
    }
    if(tiempoDisparo > 0.05)
    {
        frameDisparo++;

        tiempoDisparo = 0.0;
    }

    if(frameDisparo >= frameMaximo)
    {
        disparando = false;

        frameDisparo = 0;

        if(disparoPendiente)
        {
            disparoPendiente = false;

            tieneDisco = false;

            tiempoRecogerDisco = 0.5;

            Vector2D offsetDisparo;

            if(direccionDisparo.getX() > 0)
            {
                offsetDisparo = Vector2D(70,30);
            }
            else if(direccionDisparo.getX() < 0)
            {
                offsetDisparo = Vector2D(-70,30);
            }
            else if(direccionDisparo.getY() < 0)
            {
                offsetDisparo = Vector2D(0,-40);
            }
            else
            {
                offsetDisparo = Vector2D(0,40);
            }

            disco.setPosicion(
                jugador.getPosicion() +
                offsetDisparo
                );

            if(disparoParabolico)
            {
                proyectilActivo = true;
                tiempoProyectil = 0.0;
                posicionInicialProyectil =disco.getPosicion();
                velocidadInicialProyectil =potenciaDisparo * 2;
            }
            else
            {
                disco.setVelocidad(
                    direccionDisparo *
                    (potenciaDisparo * 5)
                    );
            }

            potencia = 0.0;
        }

        return;
    }

    itemJugador->setPixmap(
        spriteSheetDisparo.copy(
            frameReal * 135+20,
            fila * 147,
            135,
            147
            )
        );
}
void NivelEnfrentamiento::reiniciarDisco()
{
    disco.setPosicion(
        Vector2D(
            645,
            312
            )
        );

    disco.setVelocidad(
        Vector2D(
            0,
            0
            )
        );

    tieneDisco = false;
    rival.setTieneDisco(false);

    potencia = 0.0;

    cargandoDisparo = false;

    tiempoRecogerDisco = 0.5;
    proyectilActivo = false;

    disparoParabolico = false;

    tiempoProyectil = 0.0;
}
void NivelEnfrentamiento::verificarGol()
{
    if(arcoRival.detectarGol(disco))
    {
        golesJugador++;
        reiniciarDisco();
    }

    if(arcoJugador.detectarGol(disco))
    {
        golesRival++;

        reiniciarDisco();
    }
}
void NivelEnfrentamiento::activarDisparoParabolico(){
    disparoParabolico = true;
}
void NivelEnfrentamiento::intentarRobo()
{

    double distancia =
        jugador.getPosicion().distancia(
            rival.getPosicion()
            );

    if(distancia > RANGO_ROBO)
    {
        return;
    }

    if(rival.getTieneDisco())
    {
        rival.setTieneDisco(false);

        tieneDisco = true;

        tiempoRecogerDisco = 0.2;
    }
}
void NivelEnfrentamiento::generarObstaculos()
{
    eliminarObstaculos();

    for(int i = 0; i < 15; i++)
    {
        double x =
            LIMITE_IZQUIERDO +
            rand() %
                static_cast<int>(
                    LIMITE_DERECHO -
                    LIMITE_IZQUIERDO
                    );

        double y =
            LIMITE_SUPERIOR +
            rand() %
                static_cast<int>(
                    LIMITE_INFERIOR -
                    LIMITE_SUPERIOR
                    );
        Vector2D posicionObstaculo(
            x + 15,
            y + 15
            );
        int spriteAleatorio =
            rand() % 5;

        QPixmap sprite;
        switch(spriteAleatorio)
        {
        case 0:
            sprite = spriteSheetObstaculos.copy(
                370,
                0,
                160,
                147
                );
            break;

        case 1:
            sprite = spriteSheetObstaculos.copy(
                0,
                290,
                170,
                147
                );
            break;

        case 2:
            sprite = spriteSheetObstaculos.copy(
                170,
                294,
                120,
                147
                );
            break;

        case 3:
            sprite = spriteSheetObstaculos.copy(
                350,
                294,
                170,
                147
                );
            break;

        default:
            sprite = spriteSheetObstaculos.copy(
                350,
                441,
                180,
                147
                );
            break;
        }
        bool posicionValida = true;

        if(
            posicionObstaculo.distancia(
                jugador.getPosicion()
                ) < 100
            )
        {
            posicionValida = false;
        }

        if(
            posicionObstaculo.distancia(
                rival.getPosicion()
                ) < 100
            )
        {
            posicionValida = false;
        }

        if(
            posicionObstaculo.distancia(
                disco.getPosicion()
                ) < 100
            )
        {
            posicionValida = false;
        }

        if(!posicionValida)
        {
            i--;
            continue;
        }
        QGraphicsPixmapItem* itemObstaculo =
            scene->addPixmap(
                sprite
                );

        itemObstaculo->setScale(
            0.3
            );

        itemObstaculo->setPos(
            x - 30,
            y - 30
            );

        itemsObstaculos.push_back(
            itemObstaculo
            );

        posicionesObstaculos.push_back(
            Vector2D(x, y)
            );
    }
}
void NivelEnfrentamiento::eliminarObstaculos()
{
    for(auto obstaculo : itemsObstaculos)
    {
        scene->removeItem(
            obstaculo
            );

        delete obstaculo;
    }

    itemsObstaculos.clear();

    posicionesObstaculos.clear();
}
