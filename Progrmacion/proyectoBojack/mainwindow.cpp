#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),

    nivel(100.0, 100.0)
{
    ui->setupUi(this);

    // CREAR ESCENA
    scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);

    ui->graphicsView->setFixedSize(800, 600);

    scene->setSceneRect(0, 0, 100, 100);

    // INICIAR NIVEL
    nivel.iniciar();

    // CREAR JUGADOR GRAFICO
    jugadorGrafico = scene->addEllipse(
        0,
        0,
        10,
        10
        );

    // CREAR DISCO GRAFICO
    discoGrafico = scene->addEllipse(
        0,
        0,
        6,
        6
        );

    // TIMER
    timer = new QTimer(this);

    connect(
        timer,
        &QTimer::timeout,
        this,
        &MainWindow::actualizarJuego
        );

    timer->start(16);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actualizarJuego()
{
    double dt = 0.016;

    nivel.actualizar(dt);

    // ACTUALIZAR POSICION JUGADOR
    Vector2D posJugador =
        nivel.getJugador().getPosicion();

    jugadorGrafico->setPos(
        posJugador.getX(),
        posJugador.getY()
        );

    // ACTUALIZAR POSICION DISCO
    Vector2D posDisco =
        nivel.getDisco().getPosicion();

    discoGrafico->setPos(
        posDisco.getX(),
        posDisco.getY()
        );
}
