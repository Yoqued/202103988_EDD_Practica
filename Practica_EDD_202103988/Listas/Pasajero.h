#ifndef PASAJERO_H
#define PASAJERO_H

#include <string>

struct Pasajero{
    std::string nombre;
    std::string nacionalidad;
    std::string numero_de_pasaporte;
    std::string vuelo;
    int asiento;
    std::string destino;
    std::string origen;
    int equipaje_facturado;
};

#endif //PASAJERO_H
