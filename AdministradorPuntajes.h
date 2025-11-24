#ifndef ADMINISTRADORPUNTAJES_H
#define ADMINISTRADORPUNTAJES_H

#include <string>

class AdministradorPuntajes {
private:
    struct NodoPuntaje {
        std::string nombreJugador;
        int mejorPuntaje;
        NodoPuntaje* izquierda;
        NodoPuntaje* derecha;

        NodoPuntaje(const std::string &nombre, int puntaje)
            : nombreJugador(nombre),
              mejorPuntaje(puntaje),
              izquierda(nullptr),
              derecha(nullptr) {}
    };

    NodoPuntaje* raiz;

    NodoPuntaje* insertarOActualizar(NodoPuntaje* nodo,
                                     const std::string &nombreJugador,
                                     int puntaje);
    NodoPuntaje* buscar(NodoPuntaje* nodo,
                        const std::string &nombreJugador) const;
    void imprimirEnOrden(NodoPuntaje* nodo) const;
    void liberarArbol(NodoPuntaje* nodo);

public:
    AdministradorPuntajes();
    ~AdministradorPuntajes();

    void agregarPuntaje(const std::string &nombreJugador, int puntaje);
    bool obtenerPuntaje(const std::string &nombreJugador, int &puntajeSalida) const;
    void imprimirPuntajes() const;
};

#endif // ADMINISTRADORPUNTAJES_H
