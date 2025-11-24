#ifndef TIPOTESORO_H
#define TIPOTESORO_H

#include <string>

enum class TipoTesoro {
    Ninguno = 0,
    Rubi,
    Diamante,
    Perla,
    Ambar
};

std::string tipoTesoroATexto(TipoTesoro tipo);

#endif // TIPOTESORO_H
