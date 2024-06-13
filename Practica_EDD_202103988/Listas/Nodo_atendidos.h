#ifndef NODO_ATENDIDOS_H
#define NODO_ATENDIDOS_H

#include "Pasajero.h"

struct Nodo_atendidos {
    Pasajero pasajero;
    Nodo_atendidos* siguiente;
    Nodo_atendidos* anterior;

    Nodo_atendidos(Pasajero pa) : pasajero(pa), siguiente(nullptr), anterior(nullptr) {}
};

#endif //NODO_ATENDIDOS_H
