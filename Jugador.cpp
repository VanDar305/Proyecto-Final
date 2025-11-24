#include "Jugador.h"

Jugador::Jugador()
    : nombre("Jugador") {}

Jugador::Jugador(const std::string &nombre)
    : nombre(nombre) {}

void Jugador::establecerNombre(const std::string &nombre) {
    this->nombre = nombre;
}

const std::string& Jugador::obtenerNombre() const {
    return nombre;
}
