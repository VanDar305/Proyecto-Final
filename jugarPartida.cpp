while (!partidaTerminada) {

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    std::cout << "\n========================================\n";
    std::cout << "Jugador: " << jugador.obtenerNombre()
              << " Puntaje (movimientos): " << puntaje
              << " Tesoros recogidos: " << tesorosRecolectados << "/10\n";
    std::cout << "Controles: W,S,A,D / T(Ver tesoros), X(Usar), Q(Salir)\n";
    std::cout << "========================================\n\n";

    tablero.imprimir();

