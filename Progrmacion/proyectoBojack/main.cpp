#include <iostream>

#include "disco.h"
#include "jugador.h"
#include "vector2d.h"

using namespace std;

int main() {

    // =========================
    // CREACION DEL DISCO
    // =========================

    Disco disco(Vector2D(20.0, 0.0), Vector2D(0.0, 0.0), 2.0, Disco::MASA_BASE,
                Disco::FRICCION_BASE, Disco::REBOTE_BASE,
                Disco::VELOCIDAD_MAXIMA_BASE);

    // =========================
    // CREACION DEL JUGADOR
    // =========================

    Jugador jugador("Bojack", Vector2D(0.0, 0.0), 3.0,
                    Jugador::VELOCIDAD_MAXIMA_BASE, Jugador::ACELERACION_BASE,
                    Jugador::FUERZA_DISPARO_BASE, Jugador::ALCANCE_GOLPE_BASE);

    double dt = 1.0;

    // =========================
    // INFO INICIAL
    // =========================

    cout << "=========================\n";
    cout << "ESTADO INICIAL\n";
    cout << "=========================\n\n";

    cout << "Jugador: " << jugador.getNombre() << endl;

    cout << "Posicion jugador: " << jugador.getPosicion() << endl;

    cout << "Posicion disco: " << disco.getPosicion() << endl;

    cout << endl;

    // =========================
    // MOVIMIENTO DEL JUGADOR
    // =========================

    cout << "=========================\n";
    cout << "MOVIMIENTO JUGADOR\n";
    cout << "=========================\n\n";

    for (int i = 1; i <= 5; i++) {

        jugador.moverEnDireccion(Vector2D(1.0, 0.0), dt);

        jugador.actualizar(dt);

        cout << "Frame " << i << endl;

        cout << "Posicion: " << jugador.getPosicion() << endl;

        cout << "Velocidad: " << jugador.getVelocidad() << endl;

        cout << endl;
    }

    // =========================
    // PRUEBA DE ALCANCE
    // =========================

    cout << "=========================\n";
    cout << "PRUEBA DE ALCANCE\n";
    cout << "=========================\n\n";

    if (jugador.puedeGolpear(disco)) {

        cout << "El disco ESTA en rango\n";
    } else {

        cout << "El disco NO esta en rango\n";
    }

    cout << endl;

    // =========================
    // ACERCAR DISCO
    // =========================

    cout << "=========================\n";
    cout << "ACERCANDO DISCO\n";
    cout << "=========================\n\n";

    disco.setPosicion(Vector2D(46.0, 0.0));

    cout << "Nueva posicion disco: " << disco.getPosicion() << endl;

    cout << endl;

    // =========================
    // NUEVA PRUEBA DE ALCANCE
    // =========================

    cout << "=========================\n";
    cout << "NUEVA PRUEBA DE ALCANCE\n";
    cout << "=========================\n\n";

    if (jugador.puedeGolpear(disco)) {

        cout << "El disco ESTA en rango\n";
    } else {

        cout << "El disco NO esta en rango\n";
    }

    cout << endl;

    // =========================
    // DISPARO
    // =========================

    cout << "=========================\n";
    cout << "DISPARO\n";
    cout << "=========================\n\n";

    jugador.disparar(disco, Vector2D(1.0, 1.0));

    cout << "Velocidad disco despues disparo:\n";

    cout << disco.getVelocidad() << endl;

    cout << endl;

    // =========================
    // SIMULACION DEL DISCO
    // =========================

    cout << "=========================\n";
    cout << "SIMULACION DISCO\n";
    cout << "=========================\n\n";

    for (int i = 1; i <= 5; i++) {

        disco.actualizar(dt);

        cout << "Frame " << i << endl;

        cout << "Posicion: " << disco.getPosicion() << endl;

        cout << "Velocidad: " << disco.getVelocidad() << endl;

        cout << endl;
    }

    // =========================
    // REBOTE
    // =========================

    cout << "=========================\n";
    cout << "REBOTE EN X\n";
    cout << "=========================\n\n";

    disco.rebotarX();

    cout << "Velocidad despues rebote:\n";

    cout << disco.getVelocidad() << endl;

    cout << endl;

    // =========================
    // PUNTUACION
    // =========================

    cout << "=========================\n";
    cout << "PUNTUACION\n";
    cout << "=========================\n\n";

    jugador.sumarPunto();

    jugador.sumarPunto();

    cout << "Puntos jugador: " << jugador.getPuntuacion() << endl;

    cout << endl;

    // =========================
    // PARAMETROS GAMEPLAY
    // =========================

    cout << "=========================\n";
    cout << "PARAMETROS GAMEPLAY\n";
    cout << "=========================\n\n";

    cout << "Velocidad maxima jugador: " << jugador.getVelocidadMaxima() << endl;

    cout << "Aceleracion jugador: " << jugador.getAceleracion() << endl;

    cout << "Fuerza disparo jugador: " << jugador.getFuerzaDisparo() << endl;

    cout << "Alcance golpe jugador: " << jugador.getAlcanceGolpe() << endl;

    cout << endl;

    return 0;
}
