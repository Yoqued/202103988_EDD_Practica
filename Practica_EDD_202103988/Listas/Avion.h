#ifndef AVION_H
#define AVION_H

#include <string>

struct Avion {
    std::string vuelo;
    std::string numero_de_registro;
    std::string modelo;
    std::string fabricante;
    int ano_fabricacion;
    int capacidad;
    int peso_max_despegue;
    std::string aerolinea;
    std::string estado;
};

#endif //AVION_H
