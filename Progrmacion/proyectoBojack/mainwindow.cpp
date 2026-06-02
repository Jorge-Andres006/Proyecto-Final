#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->labelGoles->hide();
    ui->Pausa->hide();
    ui->AyudaPanel->hide();
    resize(1280, 720);

    enNivel = false;
    nivelActual = 0;
    cargando = false;

    setFixedSize(1280, 720);

    scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);

    ui->graphicsView->setHorizontalScrollBarPolicy(
        Qt::ScrollBarAlwaysOff);

    ui->graphicsView->setVerticalScrollBarPolicy(
        Qt::ScrollBarAlwaysOff);


    audioMenu = new QAudioOutput(this);
    audioNivel1 = new QAudioOutput(this);
    audioNivel2 = new QAudioOutput(this);
    audioVictoria = new QAudioOutput(this);

    musicaMenu = new QMediaPlayer(this);
    musicaNivel1 = new QMediaPlayer(this);
    musicaNivel2 = new QMediaPlayer(this);
    sonidoVictoria = new QMediaPlayer(this);

    musicaMenu->setAudioOutput(audioMenu);
    musicaNivel1->setAudioOutput(audioNivel1);
    musicaNivel2->setAudioOutput(audioNivel2);
    sonidoVictoria->setAudioOutput(audioVictoria);

    musicaMenu->setSource(
        QUrl("qrc:/new/prefix1/Imagenes/BoJackIntro.wav")
        );
    musicaNivel1->setSource(
        QUrl("qrc:/new/prefix1/Imagenes/MusicaNivel1.wav")
        );
    sonidoVictoria->setSource(
        QUrl(
            "qrc:/new/prefix1/Imagenes/Victoria.wav")
        );
    audioMenu->setVolume(0.35);

    audioNivel1->setVolume(0.1);

    audioNivel2->setVolume(0.35);
    audioVictoria->setVolume(1.0);

    musicaMenu->setLoops(QMediaPlayer::Infinite);
    musicaNivel1->setLoops(QMediaPlayer::Infinite);

    juego = new Juego(scene);
    juego->mostrarMenu();
    musicaMenu->play();

    connect(
        ui->botonNivel1,
        &QPushButton::clicked,
        this,
        &MainWindow::iniciarNivel1
        );
    connect(
        ui->botonNivel2,
        &QPushButton::clicked,
        this,
        &MainWindow::iniciarNivel2
        );
    connect(
        ui->botonSalir,
        &QPushButton::clicked,
        this,
        &MainWindow::close
        );
    connect(
        ui->Continuar,
        &QPushButton::clicked,
        ui->Pausa,
        &QWidget::hide
        );
    connect(
        ui->Principal,
        &QPushButton::clicked,
        this,
        &MainWindow::volverMenu
        );
    connect(
        ui->Salir,
        &QPushButton::clicked,
        this,
        &MainWindow::close
        );
    connect(
        ui->Nivel1,
        &QPushButton::clicked,
        this,
        [this]()
        {
            ui->tituloPausa->setText(
                "PAUSA"
                );
            ui->tituloPausa->setStyleSheet(
                "QLabel{"
                "color:white;"
                "font-size:28px;"
                "font-weight:bold;"
                "background:transparent;"
                "}"
                );
            ui->labelGoles->setStyleSheet(
                "QLabel{"
                "color:white;"
                "background-color:rgb(95,168,211);"
                "border-radius:8px;"
                "font-weight:bold;"
                "}"
                );
            ui->Continuar->show();
            musicaNivel1->stop();
            musicaNivel2->stop();
            musicaMenu->play();
            nivelActual = 1;
            ui->labelGoles->hide();
            ui->Pausa->hide();
            cargando = true;
            juego->mostrarPantallaCarga(1);
        }
        );
    connect(
        ui->Nivel2,
        &QPushButton::clicked,
        this,
        [this]()
        {
            ui->tituloPausa->setText(
                "PAUSA"
                );
            ui->tituloPausa->setStyleSheet(
                "QLabel{"
                "color:white;"
                "font-size:28px;"
                "font-weight:bold;"
                "background:transparent;"
                "}"
                );
            ui->Continuar->show();
            musicaNivel1->stop();
            musicaNivel2->stop();
            musicaMenu->play();
            nivelActual = 2;
            ui->labelGoles->hide();
            ui->Pausa->hide();
            cargando = true;
            juego->mostrarPantallaCarga(2);
        }
        );
    connect(
        ui->Reiniciar,
        &QPushButton::clicked,
        this,
        [this]()
        {
            ui->tituloPausa->setText(
                "PAUSA"
                );
            ui->tituloPausa->setStyleSheet(
                "QLabel{"
                "color:white;"
                "font-size:28px;"
                "font-weight:bold;"
                "background:transparent;"
                "}"
                );
            ui->labelGoles->setStyleSheet(
                "QLabel{"
                "color:white;"
                "background-color:rgb(95,168,211);"
                "border-radius:8px;"
                "font-weight:bold;"
                "}"
                );
            ui->Continuar->show();
            musicaNivel1->stop();
            musicaNivel2->stop();
            musicaMenu->play();
            ui->labelGoles->hide();
            ui->Pausa->hide();
            cargando = true;
            juego->mostrarPantallaCarga(nivelActual);
        }
        );
    connect(
        juego,
        &Juego::nivelCargado,
        this,
        [this](int nivel)
        {
            cargando = false;

            musicaMenu->stop();

            if(nivel == 1)
            {
                ui->labelGoles->show();

                musicaNivel1->play();
            }
            else if(nivel == 2)
            {
                ui->labelGoles->hide();

                musicaNivel2->play();
            }
        }
    );
    connect(
        juego,
        &Juego::golesActualizados,
        this,
        [this](int goles)
        {
            ui->labelGoles->setText(
                QString("%1/7").arg(goles)
                );

            if(goles >= 7)
            {
                ui->labelGoles->setStyleSheet(
                    "QLabel{"
                    "color:black;"
                    "background-color:rgb(255,215,0);"
                    "border-radius:8px;"
                    "font-weight:bold;"
                    "}"
                    );
            }
        }
        );
    connect(
        juego,
        &Juego::nivelCompletado,
        this,
        &MainWindow::mostrarVictoria
        );
    connect(
        ui->Ayuda,
        &QPushButton::clicked,
        this,
        [this]()
        {
            ui->Pausa->hide();

            ui->AyudaPanel->show();
        }
        );
    connect(
        ui->VolverAyuda,
        &QPushButton::clicked,
        this,
        [this]()
        {
            ui->AyudaPanel->hide();

            ui->Pausa->show();
        }
        );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iniciarNivel1()
{
    ui->labelGoles->setStyleSheet(
        "QLabel{"
        "color:white;"
        "background-color:rgb(95,168,211);"
        "border-radius:8px;"
        "font-weight:bold;"
        "}"
        );
    ui->Continuar->show();
    enNivel = true;
    nivelActual = 1;

    ui->labelGoles->hide();

    ui->botonNivel1->hide();

    ui->botonNivel2->hide();

    ui->botonSalir->hide();

    cargando = true;

    juego->mostrarPantallaCarga(1);
}

void MainWindow::iniciarNivel2()
{

    ui->Continuar->show();
    enNivel = true;
    nivelActual = 2;

    ui->labelGoles->hide();
    ui->botonNivel1->hide();

    ui->botonNivel2->hide();

    ui->botonSalir->hide();

    cargando = true;

    juego->mostrarPantallaCarga(2);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
    {
        return;
    }

    if(cargando)
    {
        return;
    }


    if(event->key() == Qt::Key_Escape &&
        ui->AyudaPanel->isVisible())
    {
        ui->AyudaPanel->hide();

        ui->Pausa->show();

        return;
    }

    if(event->key() == Qt::Key_Escape && enNivel)
    {
        if(ui->Pausa->isVisible())
        {
            ui->Pausa->hide();

            if(nivelActual == 1)
            {
                ui->labelGoles->show();
            }
        }
        else
        {
            ui->Pausa->show();

            ui->labelGoles->hide();
        }
    }

    if(enNivel)
    {
        juego->teclaPresionada(
            event->key()
            );
    }

    QMainWindow::keyPressEvent(event);
}
void MainWindow::keyReleaseEvent(
    QKeyEvent *event
    )
{
    if(event->isAutoRepeat())
    {
        return;
    }
    juego->teclaLiberada(
        event->key()
        );

    QMainWindow::keyReleaseEvent(
        event
        );
}
void MainWindow::volverMenu()
{

    ui->labelGoles->hide();
    musicaNivel1->stop();
    musicaNivel2->stop();
    musicaMenu->play();
    enNivel = false;
    nivelActual = 0;

    juego->mostrarMenu();
    ui->labelGoles->hide();
    ui->Pausa->hide();
    ui->AyudaPanel->hide();

    ui->botonNivel1->show();
    ui->botonNivel2->show();
    ui->botonSalir->show();

}
void MainWindow::mostrarVictoria()
{
    juego->pausarJuego();

    musicaNivel1->stop();
    sonidoVictoria->stop();
    ui->labelGoles->hide();
    sonidoVictoria->play();
    ui->tituloPausa->setText(
        " NIVEL COMPLETADO "
        );
    ui->tituloPausa->setStyleSheet(
        "QLabel{"
        "color:rgb(255,215,0);"
        "font-size:32px;"
        "font-weight:bold;"
        "background:transparent;"
        "}"
        );
    ui->Pausa->show();

    ui->Continuar->hide();
}
