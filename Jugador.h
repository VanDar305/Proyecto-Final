#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>

class Jugador {
public:
    Jugador();
    explicit Jugador(const std::string &nombre);

    void establecerNombre(const std::string &nombre);
    const std::string& obtenerNombre() const;

private:
    std::string nombre;
};

#endif // JUGADOR_H
