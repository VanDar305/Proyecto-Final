#include "Celda.h"

Celda::Celda(int fila, int columna)
    : fila(fila),
      columna(columna),
      esMuroBorde(false),
      esMuroInterno(false),
      descubierta(false),
      tieneJugador(false),
      tieneTesoro(false),
      tesoro(TipoTesoro::Ninguno),
      arriba(nullptr),
      abajo(nullptr),
      izquierda(nullptr),
      derecha(nullptr) {}

char Celda::caracterMostrar() const {
    if (tieneJugador) return 'P';
    if (esMuroBorde) return '#';
    if (!descubierta) return 'o';
    if (esMuroInterno) return '|';
    return ' ';
}
