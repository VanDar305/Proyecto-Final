#include "TipoTesoro.h"

std::string tipoTesoroATexto(TipoTesoro tipo) {
    switch (tipo) {
        case TipoTesoro::Rubi:      return "Rubi";
        case TipoTesoro::Diamante:  return "Diamante";
        case TipoTesoro::Perla:     return "Perla";
        case TipoTesoro::Ambar:     return "Ambar";
        default:                    return "Ninguno";
    }
}
