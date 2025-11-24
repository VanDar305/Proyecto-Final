#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Juego.h"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Juego juego;
    juego.menuPrincipal();

    return 0;
}

