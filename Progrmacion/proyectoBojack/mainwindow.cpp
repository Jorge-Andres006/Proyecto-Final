#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Pausa->hide();
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

    musicaMenu = new QMediaPlayer(this);
    musicaNivel1 = new QMediaPlayer(this);
    musicaNivel2 = new QMediaPlayer(this);
    musicaMenu->setAudioOutput(audioMenu);
    musicaNivel1->setAudioOutput(audioNivel1);
    musicaNivel2->setAudioOutput(audioNivel2);
    musicaMenu->setSource(
        QUrl("qrc:/new/prefix1/Imagenes/BoJackIntro.wav")
        );
    audioMenu->setVolume(0.35);

    audioNivel1->setVolume(0.35);

    audioNivel2->setVolume(0.35);
    musicaMenu->setLoops(QMediaPlayer::Infinite);

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
            musicaNivel1->stop();
            musicaNivel2->stop();
            musicaMenu->play();
            nivelActual = 1;
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
            musicaNivel1->stop();
            musicaNivel2->stop();
            musicaMenu->play();
            nivelActual = 2;
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
            musicaNivel1->stop();
            musicaNivel2->stop();
            musicaMenu->play();
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
                musicaNivel1->play();
            }
            else if(nivel == 2)
            {
                musicaNivel2->play();
            }
        }
        );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iniciarNivel1()
{
    enNivel = true;
    nivelActual = 1;

    ui->botonNivel1->hide();

    ui->botonNivel2->hide();

    ui->botonSalir->hide();

    cargando = true;

    juego->mostrarPantallaCarga(1);
}

void MainWindow::iniciarNivel2()
{
    enNivel = true;
    nivelActual = 2;

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
    if(event->key() == Qt::Key_Escape && enNivel)
    {
        if(ui->Pausa->isVisible())
        {
            ui->Pausa->hide();
        }
        else
        {
            ui->Pausa->show();
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
    musicaNivel1->stop();
    musicaNivel2->stop();
    musicaMenu->play();
    enNivel = false;
    nivelActual = 0;

    juego->mostrarMenu();

    ui->Pausa->hide();

    ui->botonNivel1->show();
    ui->botonNivel2->show();
    ui->botonSalir->show();

}
