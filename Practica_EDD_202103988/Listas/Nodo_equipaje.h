#ifndef NODO_EQUIPAJE_H
#define NODO_EQUIPAJE_H

#include "Equipaje.h"

struct Nodo_equipaje{
    Equipaje equipaje;
    Nodo_equipaje* siguiente;
    Nodo_equipaje* anterior;

    Nodo_equipaje(Equipaje e): equipaje(e), siguiente(nullptr), anterior(nullptr){}
};

#endif //NODO_EQUIPAJE_H
