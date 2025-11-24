#include "Juego.h"
#include <iostream>
#include <cctype>
#include <limits>

Juego::Juego() {}

void Juego::imprimirPilaTesoros(std::stack<TipoTesoro> pilaTesoros) {
    if (pilaTesoros.empty()) {
        std::cout << "No has recogido tesoros aun.\n";
        return;
    }
    std::cout << "Tesoros (del ultimo al primero):\n";
    int indice = 1;
    while (!pilaTesoros.empty()) {
        TipoTesoro tesoro = pilaTesoros.top();
        pilaTesoros.pop();
        std::cout << indice << ". " << tipoTesoroATexto(tesoro) << '\n';
        indice++;
    }
}

void Juego::jugarPartida() {
    std::string nombreJugador;
    std::cout << "Ingrese su nombre: ";
    std::getline(std::cin, nombreJugador);
    if (nombreJugador.empty()) nombreJugador = "Jugador";

    Jugador jugador(nombreJugador);

    Tablero tablero;
    int puntaje = 0;
    int tesorosRecolectados = 0;
    std::stack<TipoTesoro> pilaTesoros;
    bool partidaTerminada = false;

    while (!partidaTerminada) {
        std::cout << "\n========================================\n";
        std::cout << "Jugador: " << jugador.obtenerNombre()
                  << " Puntaje (movimientos): " << puntaje
                  << " Tesoros recogidos: " << tesorosRecolectados << "/10\n";
        std::cout << " Controles: W,S,A,D";
        std::cout << " / T(Ver tesoros), X(Usar tesoro), Q(Salir de la partida)\n";
        std::cout << "========================================\n\n";

        tablero.imprimir();

        std::cout << "\nIngrese una opcion: ";
        char opcion;
        std::cin >> opcion;
        opcion = static_cast<char>(std::toupper(static_cast<unsigned char>(opcion)));

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (opcion == 'Q') {
            std::cout << "Has salido de la partida.\n";
            partidaTerminada = true;
            continue;
        }

        if (opcion == 'T') {
            imprimirPilaTesoros(pilaTesoros);
            continue;
        }

        if (opcion == 'X') {
            if (pilaTesoros.empty()) {
                std::cout << "No tienes tesoros para usar.\n";
                continue;
            }

            TipoTesoro tesoro = pilaTesoros.top();
            pilaTesoros.pop();

            std::cout << "Usaste el tesoro: " << tipoTesoroATexto(tesoro) << '\n';

            if (tesoro == TipoTesoro::Rubi) {
                puntaje /= 2;
                std::cout << "El Rubi reduce tu puntaje a la mitad. Nuevo puntaje: "
                          << puntaje << '\n';
            } else if (tesoro == TipoTesoro::Diamante) {
                tablero.eliminarMurosInternosAleatorios(2);
                std::cout << "El Diamante elimina 2 muros internos aleatorios.\n";
            } else if (tesoro == TipoTesoro::Perla) {
                int aleatorio = std::rand() % 2;
                if (aleatorio == 0) {
                    puntaje = 0;
                    std::cout << "La Perla reduce tu puntaje a 0.\n";
                } else {
                    puntaje *= 2;
                    std::cout << "La Perla duplica tu puntaje. Nuevo puntaje: "
                              << puntaje << '\n';
                }
            } else if (tesoro == TipoTesoro::Ambar) {
                tablero.teletransportarJugadorAleatorio();
                std::cout << "El Ambar te teletransporta a otra parte del tablero.\n";
            }

            tablero.reinsertarTesoro(tesoro);
            tablero.reiniciarDescubrimiento();

            continue;
        }

        if (opcion == 'W' || opcion == 'A' || opcion == 'S' || opcion == 'D') {
            TipoTesoro tesoroEncontrado;
            bool hayTesoroEncontrado = false;
            bool chocoConMuro = false;

            bool movimientoValido = tablero.moverJugador(
                opcion,
                tesoroEncontrado,
                hayTesoroEncontrado,
                chocoConMuro
            );

            if (!movimientoValido) {
                std::cout << "Movimiento invalido.\n";
                continue;
            }

            puntaje++;

            if (hayTesoroEncontrado) {
                pilaTesoros.push(tesoroEncontrado);
                tesorosRecolectados++;
                if (tesorosRecolectados >= 10) {
                    std::cout << "¡Has recogido los 10 tesoros ocultos!\n";
                    partidaTerminada = true;
                }
            }

            continue;
        }

        std::cout << "Opcion no válida.\n";
    }

    if (tesorosRecolectados >= 10) {
        std::cout << "Juego terminado. Puntaje final de "
                  << jugador.obtenerNombre() << ": " << puntaje << "\n";
        administradorPuntajes.agregarPuntaje(jugador.obtenerNombre(), puntaje);
    } else {
        std::cout << "Partida sin completar. No se registra puntaje.\n";
    }
}

void Juego::mostrarPuntajeJugador() {
    std::string nombreJugador;
    std::cout << "Ingrese el nombre del jugador a buscar: ";
    std::getline(std::cin, nombreJugador);

    int puntaje;
    if (administradorPuntajes.obtenerPuntaje(nombreJugador, puntaje)) {
        std::cout << "El jugador " << nombreJugador
                  << " tiene un mejor puntaje de: " << puntaje << " movimientos.\n";
    } else {
        std::cout << "El jugador " << nombreJugador
                  << " no tiene puntaje registrado.\n";
    }
}

void Juego::mostrarRanking() {
    administradorPuntajes.imprimirPuntajes();
}

void Juego::menuPrincipal() {
    bool salir = false;
    while (!salir) {
        std::cout << "\n========================================\n";
        std::cout << "        JUEGO DE LOS LABERINTOS\n";
        std::cout << "========================================\n";
        std::cout << "1. Jugar nueva partida\n";
        std::cout << "2. Consultar puntaje de un jugador\n";
        std::cout << "3. Ver ranking de jugadores\n";
        std::cout << "4. Salir\n";
        std::cout << "Seleccione una opcion: ";

        int opcion;
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                jugarPartida();
                break;
            case 2:
                mostrarPuntajeJugador();
                break;
            case 3:
                mostrarRanking();
                break;
            case 4:
                salir = true;
                break;
            default:
                std::cout << "Opcion invalida.\n";
        }
    }
}
