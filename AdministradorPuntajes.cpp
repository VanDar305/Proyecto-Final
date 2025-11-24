#include "AdministradorPuntajes.h"
#include <iostream>

AdministradorPuntajes::AdministradorPuntajes()
    : raiz(nullptr) {}

AdministradorPuntajes::~AdministradorPuntajes() {
    liberarArbol(raiz);
}

void AdministradorPuntajes::liberarArbol(NodoPuntaje* nodo) {
    if (!nodo) return;
    liberarArbol(nodo->izquierda);
    liberarArbol(nodo->derecha);
    delete nodo;
}

AdministradorPuntajes::NodoPuntaje* AdministradorPuntajes::insertarOActualizar(
    NodoPuntaje* nodo,
    const std::string &nombreJugador,
    int puntaje) {

    if (!nodo) {
        return new NodoPuntaje(nombreJugador, puntaje);
    }

    if (nombreJugador < nodo->nombreJugador) {
        nodo->izquierda = insertarOActualizar(nodo->izquierda, nombreJugador, puntaje);
    } else if (nombreJugador > nodo->nombreJugador) {
        nodo->derecha = insertarOActualizar(nodo->derecha, nombreJugador, puntaje);
    } else {
        if (puntaje < nodo->mejorPuntaje) {
            nodo->mejorPuntaje = puntaje;
        }
    }

    return nodo;
}

AdministradorPuntajes::NodoPuntaje* AdministradorPuntajes::buscar(
    NodoPuntaje* nodo,
    const std::string &nombreJugador) const {

    if (!nodo) return nullptr;
    if (nombreJugador == nodo->nombreJugador) return nodo;
    if (nombreJugador < nodo->nombreJugador) {
        return buscar(nodo->izquierda, nombreJugador);
    }
    return buscar(nodo->derecha, nombreJugador);
}

void AdministradorPuntajes::imprimirEnOrden(NodoPuntaje* nodo) const {
    if (!nodo) return;
    imprimirEnOrden(nodo->izquierda);
    std::cout << "Jugador: " << nodo->nombreJugador
              << " | Mejor puntaje: " << nodo->mejorPuntaje << '\n';
    imprimirEnOrden(nodo->derecha);
}

void AdministradorPuntajes::agregarPuntaje(const std::string &nombreJugador,
                                           int puntaje) {
    raiz = insertarOActualizar(raiz, nombreJugador, puntaje);
}

bool AdministradorPuntajes::obtenerPuntaje(const std::string &nombreJugador,
                                           int &puntajeSalida) const {
    NodoPuntaje* nodo = buscar(raiz, nombreJugador);
    if (!nodo) return false;
    puntajeSalida = nodo->mejorPuntaje;
    return true;
}

void AdministradorPuntajes::imprimirPuntajes() const {
    if (!raiz) {
        std::cout << "No hay puntajes registrados.\n";
        return;
    }
    std::cout << "Puntajes (del menor al mayor):\n";
    imprimirEnOrden(raiz);
}
