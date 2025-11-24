#ifndef TABLERO_H
#define TABLERO_H

#include <list>
#include "Celda.h"

class Tablero {
public:
    Tablero();
    ~Tablero();

    void inicializar();
    void imprimir() const;
    void reiniciarDescubrimiento();

    bool moverJugador(char direccion,
                      TipoTesoro &tesoroEncontrado,
                      bool &hayTesoroEncontrado,
                      bool &chocoConMuro);

    void reinsertarTesoro(TipoTesoro tesoro);
    void eliminarMurosInternosAleatorios(int cantidad);
    void teletransportarJugadorAleatorio();

private:
    static const int FILAS = 9;
    static const int COLUMNAS = 9;

    Celda* celdaInicial;
    Celda* celdaJugador;

    void construirCuadricula();
    void liberarCuadricula();

    std::list<Celda*> obtenerTodasLasCeldas() const;
    std::list<Celda*> obtenerCeldasParaTesoro() const;
    std::list<Celda*> obtenerCeldasParaMuroInterno() const;
    std::list<Celda*> obtenerCeldasParaTeletransporte() const;

    Celda* celdaAleatoriaDesdeLista(const std::list<Celda*> &listaCeldas) const;

    void ubicarTesoros(int cantidad);
    void ubicarMurosInternos(int cantidad);
    void ubicarJugadorAleatoriamente();
};

#endif // TABLERO_H
