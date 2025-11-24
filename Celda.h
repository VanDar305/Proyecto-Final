#ifndef CELDA_H
#define CELDA_H

#include "TipoTesoro.h"

class Celda {
public:
    int fila;
    int columna;

    bool esMuroBorde;
    bool esMuroInterno;
    bool descubierta;
    bool tieneJugador;
    bool tieneTesoro;
    TipoTesoro tesoro;

    Celda* arriba;
    Celda* abajo;
    Celda* izquierda;
    Celda* derecha;

    Celda(int fila, int columna);

    char caracterMostrar() const;
};

#endif // CELDA_H
