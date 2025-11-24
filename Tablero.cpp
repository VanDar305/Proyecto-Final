#include "Tablero.h"
#include <iostream>
#include <cstdlib>

Tablero::Tablero()
    : celdaInicial(nullptr),
      celdaJugador(nullptr) {
    construirCuadricula();
    inicializar();
}

Tablero::~Tablero() {
    liberarCuadricula();
}

void Tablero::construirCuadricula() {
    Celda* primerCeldaFilaAnterior = nullptr;
    celdaInicial = nullptr;

    for (int fila = 0; fila < FILAS; ++fila) {
        Celda* primeraCeldaFila = nullptr;
        Celda* celdaAnterior = nullptr;
        Celda* celdaArriba = primerCeldaFilaAnterior;

        for (int columna = 0; columna < COLUMNAS; ++columna) {
            Celda* celdaActual = new Celda(fila, columna);

            if (!celdaInicial) {
                celdaInicial = celdaActual;
            }
            if (!primeraCeldaFila) {
                primeraCeldaFila = celdaActual;
            }

            if (celdaAnterior) {
                celdaAnterior->derecha = celdaActual;
                celdaActual->izquierda = celdaAnterior;
            }

            if (celdaArriba) {
                celdaActual->arriba = celdaArriba;
                celdaArriba->abajo = celdaActual;
                celdaArriba = celdaArriba->derecha;
            }

            if (fila == 0 || fila == FILAS - 1 || columna == 0 || columna == COLUMNAS - 1) {
                celdaActual->esMuroBorde = true;
                celdaActual->descubierta = true;
            }

            celdaAnterior = celdaActual;
        }

        primerCeldaFilaAnterior = primeraCeldaFila;
    }
}

void Tablero::liberarCuadricula() {
    if (!celdaInicial) return;

    Celda* fila = celdaInicial;
    while (fila) {
        Celda* siguienteFila = fila->abajo;
        Celda* actual = fila;
        while (actual) {
            Celda* siguiente = actual->derecha;
            delete actual;
            actual = siguiente;
        }
        fila = siguienteFila;
    }

    celdaInicial = nullptr;
    celdaJugador = nullptr;
}

std::list<Celda*> Tablero::obtenerTodasLasCeldas() const {
    std::list<Celda*> lista;
    Celda* fila = celdaInicial;
    while (fila) {
        Celda* actual = fila;
        while (actual) {
            lista.push_back(actual);
            actual = actual->derecha;
        }
        fila = fila->abajo;
    }
    return lista;
}

std::list<Celda*> Tablero::obtenerCeldasParaTesoro() const {
    std::list<Celda*> resultado;
    auto todas = obtenerTodasLasCeldas();
    for (Celda* celda : todas) {
        if (!celda->esMuroBorde &&
            !celda->esMuroInterno &&
            !celda->tieneTesoro &&
            !celda->tieneJugador) {
            resultado.push_back(celda);
        }
    }
    return resultado;
}

std::list<Celda*> Tablero::obtenerCeldasParaMuroInterno() const {
    std::list<Celda*> resultado;
    auto todas = obtenerTodasLasCeldas();
    for (Celda* celda : todas) {
        if (!celda->esMuroBorde &&
            !celda->esMuroInterno &&
            !celda->tieneTesoro &&
            !celda->tieneJugador) {
            resultado.push_back(celda);
        }
    }
    return resultado;
}

std::list<Celda*> Tablero::obtenerCeldasParaTeletransporte() const {
    std::list<Celda*> resultado;
    auto todas = obtenerTodasLasCeldas();
    for (Celda* celda : todas) {
        if (!celda->esMuroBorde &&
            !celda->esMuroInterno &&
            !celda->tieneJugador &&
            !celda->descubierta) {
            resultado.push_back(celda);
        }
    }
    return resultado;
}

Celda* Tablero::celdaAleatoriaDesdeLista(const std::list<Celda*> &listaCeldas) const {
    if (listaCeldas.empty()) return nullptr;
    int tamano = static_cast<int>(listaCeldas.size());
    int indiceObjetivo = std::rand() % tamano;
    int indiceActual = 0;
    for (Celda* celda : listaCeldas) {
        if (indiceActual == indiceObjetivo) return celda;
        ++indiceActual;
    }
    return nullptr;
}

void Tablero::ubicarTesoros(int cantidad) {
    int colocados = 0;
    while (colocados < cantidad) {
        auto candidatas = obtenerCeldasParaTesoro();
        Celda* celda = celdaAleatoriaDesdeLista(candidatas);
        if (!celda) return;

        int tipoAleatorio = std::rand() % 4;
        TipoTesoro tipo = TipoTesoro::Rubi;
        if (tipoAleatorio == 1) tipo = TipoTesoro::Diamante;
        else if (tipoAleatorio == 2) tipo = TipoTesoro::Perla;
        else if (tipoAleatorio == 3) tipo = TipoTesoro::Ambar;

        celda->tieneTesoro = true;
        celda->tesoro = tipo;
        colocados++;
    }
}

void Tablero::ubicarMurosInternos(int cantidad) {
    int colocados = 0;
    while (colocados < cantidad) {
        auto candidatas = obtenerCeldasParaMuroInterno();
        Celda* celda = celdaAleatoriaDesdeLista(candidatas);
        if (!celda) return;

        celda->esMuroInterno = true;
        colocados++;
    }
}

void Tablero::ubicarJugadorAleatoriamente() {
    auto todas = obtenerTodasLasCeldas();
    std::list<Celda*> candidatas;
    for (Celda* celda : todas) {
        if (!celda->esMuroBorde &&
            !celda->esMuroInterno &&
            !celda->tieneTesoro) {
            candidatas.push_back(celda);
        }
    }
    Celda* celda = celdaAleatoriaDesdeLista(candidatas);
    if (!celda) return;

    celda->tieneJugador = true;
    celda->descubierta = true;
    celdaJugador = celda;
}

void Tablero::inicializar() {
    auto todas = obtenerTodasLasCeldas();
    for (Celda* celda : todas) {
        if (!celda->esMuroBorde) {
            celda->esMuroInterno = false;
            celda->tieneTesoro = false;
            celda->tesoro = TipoTesoro::Ninguno;
            celda->tieneJugador = false;
            celda->descubierta = false;
        } else {
            celda->tieneJugador = false;
            celda->tieneTesoro = false;
            celda->esMuroInterno = false;
            celda->tesoro = TipoTesoro::Ninguno;
            celda->descubierta = true;
        }
    }

    celdaJugador = nullptr;

    ubicarTesoros(10);
    ubicarMurosInternos(16);
    ubicarJugadorAleatoriamente();
}

void Tablero::imprimir() const {
    Celda* fila = celdaInicial;
    while (fila) {
        Celda* actual = fila;
        while (actual) {
            std::cout << actual->caracterMostrar() << ' ';
            actual = actual->derecha;
        }
        std::cout << '\n';
        fila = fila->abajo;
    }
}

void Tablero::reiniciarDescubrimiento() {
    auto todas = obtenerTodasLasCeldas();
    for (Celda* celda : todas) {
        if (!celda->esMuroBorde) {
            if (!celda->esMuroInterno) {
                celda->descubierta = false;
            } else {
                celda->descubierta = true;
            }
        } else {
            celda->descubierta = true;
        }
    }

    if (celdaJugador) {
        celdaJugador->descubierta = true;
    }
}

bool Tablero::moverJugador(char direccion,
                           TipoTesoro &tesoroEncontrado,
                           bool &hayTesoroEncontrado,
                           bool &chocoConMuro) {
    hayTesoroEncontrado = false;
    chocoConMuro = false;
    tesoroEncontrado = TipoTesoro::Ninguno;

    if (!celdaJugador) return false;

    Celda* celdaDestino = nullptr;
    if (direccion == 'W') celdaDestino = celdaJugador->arriba;
    else if (direccion == 'S') celdaDestino = celdaJugador->abajo;
    else if (direccion == 'A') celdaDestino = celdaJugador->izquierda;
    else if (direccion == 'D') celdaDestino = celdaJugador->derecha;

    if (!celdaDestino) {
        std::cout << "No puedes salir del laberinto.\n";
        return true;
    }

    if (celdaDestino->esMuroBorde) {
        std::cout << "Hay una pared de borde, no puedes salir del laberinto.\n";
        return true;
    }

    if (celdaDestino->esMuroInterno) {
        celdaDestino->descubierta = true;
        chocoConMuro = true;
        std::cout << "¡Has chocado con un muro interno!\n";
        return true;
    }

    celdaJugador->tieneJugador = false;

    celdaJugador = celdaDestino;
    celdaJugador->tieneJugador = true;
    celdaJugador->descubierta = true;

    if (celdaJugador->tieneTesoro) {
        hayTesoroEncontrado = true;
        tesoroEncontrado = celdaJugador->tesoro;
        std::cout << "¡Has encontrado un tesoro: "
                  << tipoTesoroATexto(tesoroEncontrado) << "!\n";
        celdaJugador->tieneTesoro = false;
        celdaJugador->tesoro = TipoTesoro::Ninguno;
    }

    return true;
}

void Tablero::reinsertarTesoro(TipoTesoro tesoro) {
    if (tesoro == TipoTesoro::Ninguno) return;

    auto candidatas = obtenerCeldasParaTesoro();
    Celda* celda = celdaAleatoriaDesdeLista(candidatas);
    if (!celda) return;

    celda->tieneTesoro = true;
    celda->tesoro = tesoro;
}

void Tablero::eliminarMurosInternosAleatorios(int cantidad) {
    int eliminados = 0;
    while (eliminados < cantidad) {
        auto todas = obtenerTodasLasCeldas();
        std::list<Celda*> muros;
        for (Celda* celda : todas) {
            if (celda->esMuroInterno) {
                muros.push_back(celda);
            }
        }
        if (muros.empty()) return;

        Celda* celda = celdaAleatoriaDesdeLista(muros);
        if (!celda) return;

        celda->esMuroInterno = false;
        eliminados++;
    }
}

void Tablero::teletransportarJugadorAleatorio() {
    auto candidatas = obtenerCeldasParaTeletransporte();
    Celda* celda = celdaAleatoriaDesdeLista(candidatas);
    if (!celda) {
        std::cout << "No hay casillas validas para teletransportar.\n";
        return;
    }

    if (celdaJugador) {
        celdaJugador->tieneJugador = false;
    }

    celdaJugador = celda;
    celdaJugador->tieneJugador = true;
    celdaJugador->descubierta = true;
}
