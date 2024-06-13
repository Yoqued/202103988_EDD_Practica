#ifndef NODO_PASAJERO_H
#define NODO_PASAJERO_H

#include "Pasajero.h"

struct Nodo_pasajero {
    Pasajero pasajero;
    Nodo_pasajero* siguiente;

    Nodo_pasajero(Pasajero p) : pasajero(p), siguiente(nullptr) {}
};

#endif //NODO_PASAJERO_H
