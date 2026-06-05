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
    spriteSheetObstaculos = QPixmap(
        ":/new/prefix1/Imagenes/Obstaculos.png"
        );
    spriteSheetDisparo = QPixmap(
        ":/new/prefix1/Imagenes/SpriteDisparoBojackH.png"
        );
    this->scene = scene;

    itemJugador = nullptr;

    itemDisco = nullptr;

    itemArco = nullptr;

    hudPotencia = nullptr;

    barraPotencia = nullptr;

    textoVidas = nullptr;
    goles = 0;

    tiempoSpawnObstaculos = 0.0;

    potencia = 0.0;
    tiempoRecogerDisco = 0.0;
    frameActual = 0;

    tiempoAnimacion = 0.0;
    frameDisparo = 0;
    tiempoDisparo = 0.0;
    potenciaDisparo = 0.0;
    vidas = 5;
    golesParaGanar = 7;

    tiempoSpawnMaximo = 0.7;


    direccionDisparo = Vector2D(1,0);

    disparoPendiente = false;
    disparando = false;
    cargandoDisparo = false;
    tieneDisco = false;
    invulnerable = false;
    perdio = false;
    dificultadDificil = false;

    tiempoInvulnerabilidad = 0.0;
    direccionJugador = Vector2D(1,0);
    audioTodd = new QAudioOutput();

    sonidoTodd = new QMediaPlayer();

    sonidoTodd->setAudioOutput(
        audioTodd
        );
    sonidoTodd->setSource(
        QUrl(
            "qrc:/new/prefix1/Imagenes/ToddAudio.wav"
            )
        );
    audioTodd->setVolume(
        1.0
        );
    audioGol = new QAudioOutput();

    sonidoGol = new QMediaPlayer();


    sonidoGol->setAudioOutput(
        audioGol
        );
    sonidoGol->setSource(
        QUrl(
            "qrc:/new/prefix1/Imagenes/CelebracionGol.wav"
            )
        );

    audioGol->setVolume(
        0.15
        );
}

NivelEntrenamiento::~NivelEntrenamiento(){
    for(Obstaculo* obstaculo : obstaculos)
    {
        delete obstaculo;
    }
    delete sonidoTodd;

    delete audioTodd;
    delete sonidoGol;

    delete audioGol;
}

void NivelEntrenamiento::iniciar()
{
    mundo.agregarEntidad(&disco);
    mundo.agregarEntidad(&jugador);
    if(dificultadDificil)
    {
        vidas = 1;
    }
    else
    {
        vidas = 5;
    }
    Obstaculo* obstaculo =new Obstaculo(
            Vector2D(
                1100,
                300
                ),
            20.0
            );

    obstaculos.push_back(
        obstaculo
        );
    QPixmap spriteObstaculo =spriteSheetObstaculos.copy(
            170,
            294,
            120,
            147
            );

    QGraphicsPixmapItem* itemObstaculo =
        scene->addPixmap(
            spriteObstaculo
            );

    itemObstaculo->setScale(0.3);

    itemObstaculo->setPos(
        obstaculo->getPosicion().getX() - 30,
        obstaculo->getPosicion().getY() - 30
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
            0,
            0,
            135,
            147
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
    textoVidas = scene->addText(
        QString(
            "Vidas: %1"
            ).arg(
                vidas
                )
        );
    QFont fuenteVidas(
        "Segoe UI",
        24,
        QFont::Bold
        );

    textoVidas->setFont(
        fuenteVidas
        );

    textoVidas->setPos(
        20,
        20
        );

    textoVidas->setDefaultTextColor(
        Qt::white
        );

    textoVidas->setZValue(
        100
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
}

void NivelEntrenamiento::actualizar(double dt)
{
    tiempoAnimacion += dt;
    tiempo += dt;
    actualizarDisparo(dt);
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
    if(tiempoSpawnObstaculos >=tiempoSpawnMaximo)
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

        if(puntoColision.distancia(obstaculo->getPosicion()) < 30.0){
            if(!invulnerable)
            {
                if(dificultadDificil)
                {
                    vidas = 0;
                }
                else
                {
                    vidas--;
                }

                textoVidas->setPlainText(
                    "Vidas: " +
                    QString::number(
                        vidas
                        )
                    );
                if(tieneDisco)
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
                }
                if(!dificultadDificil)
                {
                    invulnerable = true;

                    tiempoInvulnerabilidad = 2.0;
                }
                sonidoTodd->stop();
                sonidoTodd->play();
            }
            if(vidas <= 0)
            {
                perdio = true;

                finalizar();
            }
            if(tieneDisco && !invulnerable)
            {
                sonidoTodd->stop();

                sonidoTodd->play();
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
        itemsObstaculos[i]->setPos(
            obstaculos[i]->getPosicion().getX() - 30,
            obstaculos[i]->getPosicion().getY() - 30
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

        if(goles < golesParaGanar)
        {
            sonidoGol->stop();

            sonidoGol->play();
        }

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

        if(goles >=golesParaGanar)
        {

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
        sprite =spriteSheetObstaculos.copy(
                0,
                290,
                170,
                147
                );
        break;

    case 2:
        sprite=spriteSheetObstaculos.copy(
            170,
            294,
            120,
            147
            );
        break;

    case 3:

        sprite =spriteSheetObstaculos.copy(
                350,
                294,
                170,
                147
                );
        break;

    default:
        sprite =spriteSheetObstaculos.copy(
                350,
                441,
                180,
                147
                );
        break;
    }

    QGraphicsPixmapItem* itemObstaculo =
        scene->addPixmap(
            sprite
            );

    itemObstaculo->setScale(0.3);

    itemObstaculo->setPos(
        x - 30,
        y - 30
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


double NivelEntrenamiento::getPotencia() const
{
    return potencia;
}
void NivelEntrenamiento::moverJugador(
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
    double velocidadJugador = 1.2;

    if(tieneDisco)
    {
        velocidadJugador =0.6;
    }

    Vector2D nuevaPosicion =jugador.getPosicion() +
        direccion * velocidadJugador;

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

    for(Obstaculo* obstaculo : obstaculos)
    {
        Vector2D puntoColision =
            nuevaPosicion +
            Vector2D(0,30);

        if(
            puntoColision.distancia(
                obstaculo->getPosicion()
                ) < 35
            )
        {
            hayColision = true;
            break;
        }
    }

    if(!hayColision)
    {
        jugador.setPosicion(
            nuevaPosicion
            );
    }
}
int NivelEntrenamiento::getGoles() const
{
    return goles;
}
bool NivelEntrenamiento::getPerdio() const
{
    return perdio;
}
void NivelEntrenamiento::actualizarDisparo(double dt)
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

            disco.setVelocidad(
                direccionDisparo *
                (potenciaDisparo * 5)
                );

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
void NivelEntrenamiento::setDificultadDificil(
    bool dificil
    )
{
    dificultadDificil = dificil;

    if(dificultadDificil)
    {
        vidas = 1;

        golesParaGanar = 15;

        tiempoSpawnMaximo = 0.4;
    }
    else
    {
        vidas = 5;

        golesParaGanar = 7;

        tiempoSpawnMaximo = 0.7;
    }
}
