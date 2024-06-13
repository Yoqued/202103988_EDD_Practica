#ifndef NODO_AVION_H
#define NODO_AVION_H

#include "Avion.h"

struct Nodo_avion {
    Avion avion;
    Nodo_avion* siguiente;
    Nodo_avion* anterior;

    Nodo_avion(Avion a) : avion(a), siguiente(nullptr), anterior(nullptr) {}
};

#endif //NODO_AVION_H
