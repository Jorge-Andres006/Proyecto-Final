#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    resize(1280, 720);

    setFixedSize(1280, 720);

    scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);

    ui->graphicsView->setHorizontalScrollBarPolicy(
        Qt::ScrollBarAlwaysOff);

    ui->graphicsView->setVerticalScrollBarPolicy(
        Qt::ScrollBarAlwaysOff);

    juego = new Juego(scene);

    juego->mostrarMenu();

    audioOutput = new QAudioOutput(this);

    musicaMenu = new QMediaPlayer(this);
    musicaMenu->setAudioOutput(audioOutput);
    musicaMenu->setSource(
        QUrl("qrc:/new/prefix1/Imagenes/BoJackIntro.wav")
        );
    audioOutput->setVolume(0.35);
    musicaMenu->setLoops(QMediaPlayer::Infinite);
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iniciarNivel1()
{
    musicaMenu->stop();
    ui->botonNivel1->hide();

    ui->botonNivel2->hide();

    ui->botonSalir->hide();

    juego->iniciarNivel1();
}

void MainWindow::iniciarNivel2()
{
    musicaMenu->stop();
    ui->botonNivel1->hide();

    ui->botonNivel2->hide();

    ui->botonSalir->hide();

    juego->iniciarNivel2();
}


