// #include "mainwindow.h"

// #include <QApplication>

// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);
//     MainWindow w;
//     w.show();
//     return a.exec();
// }

#include <iostream>

#include "mundo.h"
#include "jugador.h"
#include "disco.h"

    using namespace std;

int main() {

    Mundo mundo(100, 50);

    Jugador jugador(
        "Bojack",
        Vector2D(10, 25),
        2.0,
        10.0,
        50.0,
        20.0,
        8.0
        );

    Disco disco(
        Vector2D(15, 25),
        Vector2D(0, 0),
        1.0,
        1.0,
        0.98,
        0.8,
        30.0
        );

    mundo.agregarEntidad(&jugador);

    mundo.agregarEntidad(&disco);

    double dt = 0.016;

    jugador.moverEnDireccion(Vector2D(1, 0), dt);

    jugador.disparar(disco, Vector2D(1, 0));

    for (int frame = 0; frame < 120; frame++) {

        mundo.actualizar(dt);

        cout << "=========================" << endl;

        cout << "FRAME: " << frame << endl;

        cout << "Jugador posicion: "
             << jugador.getPosicion() << endl;

        cout << "Jugador velocidad: "
             << jugador.getVelocidad() << endl;

        cout << "Disco posicion: "
             << disco.getPosicion() << endl;

        cout << "Disco velocidad: "
             << disco.getVelocidad() << endl;
    }

    return 0;
}

