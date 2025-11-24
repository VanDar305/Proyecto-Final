#ifndef JUEGO_H
#define JUEGO_H

#include <stack>
#include "Tablero.h"
#include "Jugador.h"
#include "AdministradorPuntajes.h"

class Juego {
public:
    Juego();

    void menuPrincipal();

private:
    AdministradorPuntajes administradorPuntajes;

    void jugarPartida();
    void mostrarPuntajeJugador();
    void mostrarRanking();

    void imprimirPilaTesoros(std::stack<TipoTesoro> pilaTesoros);
};

#endif // JUEGO_H
