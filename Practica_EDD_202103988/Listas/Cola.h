#ifndef COLA_H
#define COLA_H

#include "Nodo_pasajero.h"
#include <iostream>

class Cola {
private:
    Nodo_pasajero* primero;
    Nodo_pasajero* ultimo;

public:
    Cola() : primero(nullptr), ultimo(nullptr) {}

    ~Cola() {
        while (primero != nullptr) {
            Nodo_pasajero* temp = primero;
            primero = primero->siguiente;
            delete temp;
        }
        ultimo = nullptr;
    }

    bool esta_vacia() {
        return primero == nullptr;
    }

    void encolar(Nodo_pasajero valor) {
        Nodo_pasajero* nuevo = new Nodo_pasajero(valor);
        if (esta_vacia()) {
            primero = nuevo;
            ultimo = nuevo;
        } else {
            ultimo->siguiente = nuevo;
            ultimo = nuevo;
        }
    }

    Pasajero desencolar() {
        if (esta_vacia()) {
            std::cerr << "La cola está vacía" << std::endl;
            return Pasajero();
        }
        Nodo_pasajero* temp = primero;
        Pasajero valor = primero->pasajero;
        primero = primero->siguiente;
        delete temp;
        return valor;
    }

    void imprimir() {
        Nodo_pasajero* actual = primero;
        std::cout << "Contenido de la cola:" << std::endl;
        while (actual != nullptr) {
            std::cout << "Nombre: " << actual->pasajero.nombre << std::endl;
            std::cout << "Nacionalidad: " << actual->pasajero.nacionalidad << std::endl;
            std::cout << "Numero de pasaporte: " << actual->pasajero.numero_de_pasaporte << std::endl;
            std::cout << "Vuelo: " << actual->pasajero.vuelo << std::endl;
            std::cout << "Destino: " << actual->pasajero.destino << std::endl;
            std::cout << "Origen: " << actual->pasajero.origen << std::endl;
            std::cout << "Equipaje facturado: " << actual->pasajero.equipaje_facturado << std::endl;
            std::cout << "--------------------------" << std::endl;
            std::cout << std::endl;
            actual = actual->siguiente;
        }
    }

    // Método para generar el archivo DOT para Graphviz y abrirlo
    void generarDot(const std::string& nombreArchivo) const {
        std::ofstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo para escribir." << std::endl;
            return;
        }

        archivo << "digraph G {" << std::endl;
        archivo << "    node [shape=record];" << std::endl;

        Nodo_pasajero* actual = primero;
        int id = 0;
        while (actual != nullptr) {
            archivo << "    nodo" << id << " [label=\"{|Nombre: "
                    << actual->pasajero.nombre << "\\nNacionalidad: "
                    << actual->pasajero.nacionalidad << "\\nPasaporte: "
                    << actual->pasajero.numero_de_pasaporte << "\\nVuelo: "
                    << actual->pasajero.vuelo << "\\nDestino: "
                    << actual->pasajero.destino << "\\nOrigen: "
                    << actual->pasajero.origen << "\\nEquipaje: "
                    << actual->pasajero.equipaje_facturado << "|}\"];" << std::endl;
            if (actual->siguiente != nullptr) {
                archivo << "    nodo" << id << " -> nodo" << id + 1 << ";" << std::endl;
            }
            actual = actual->siguiente;
            id++;
        }

        archivo << "}" << std::endl;
        archivo.close();

        // Mensaje de confirmación para verificar que el archivo se ha creado
        std::cout << "Archivo DOT generado: " << nombreArchivo << std::endl;

        // Comando para abrir el archivo DOT con la aplicación predeterminada
        std::string comando = "dot -Tpng " + nombreArchivo + " -o " + nombreArchivo + ".png";
        int result = std::system(comando.c_str());

        // Verificar si el comando se ejecutó correctamente
        if (result == 0) {
            // Abrir la imagen generada
#ifdef _WIN32
            std::string openCommand = "start " + nombreArchivo + ".png";
#elif __APPLE__
            std::string openCommand = "open " + nombreArchivo + ".png";
#else
            std::string openCommand = "xdg-open " + nombreArchivo + ".png";
#endif
            std::system(openCommand.c_str());
        } else {
            std::cerr << "Error al generar la imagen PNG con Graphviz." << std::endl;
        }
    }

    bool buscar_por_pasaporte(const std::string& numero_de_pasaporte) {
        Nodo_pasajero* actual = primero;
        while (actual != nullptr) {
            if (actual->pasajero.numero_de_pasaporte == numero_de_pasaporte) {
                std::cout << "------------------------------------------ \n";
                std::cout << "Nombre: " << actual->pasajero.nombre << std::endl;
                std::cout << "Pasaporte: " << actual->pasajero.numero_de_pasaporte << std::endl;
                std::cout << "Vuelo: " << actual->pasajero.vuelo << std::endl;
                std::cout << "Asiento: " << actual->pasajero.asiento << std::endl;
                std::cout << "Destino: " << actual->pasajero.destino << std::endl;
                std::cout << "Origen: " << actual->pasajero.origen << std::endl;
                std::cout << "Equipaje: " << actual->pasajero.equipaje_facturado << std::endl;
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }

};

#endif //COLA_H
