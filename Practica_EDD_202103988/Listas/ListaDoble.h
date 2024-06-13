#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include "Nodo_atendidos.h"
#include <iostream>

class ListaDoble {
private:
    Nodo_atendidos* cabeza;

public:
    ListaDoble() : cabeza(nullptr) {}

    // Destructor para liberar la memoria de los nodos
    ~ListaDoble() {
        Nodo_atendidos* actual = cabeza;
        while (actual != nullptr) {
            Nodo_atendidos* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
        cabeza = nullptr;
    }

    // Método para añadir al final de la lista
    void agregarFinal(Pasajero pa) {
        Nodo_atendidos* nuevo_nodo = new Nodo_atendidos(pa);
        if (cabeza == nullptr) {
            cabeza = nuevo_nodo;
        } else {
            Nodo_atendidos* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo_nodo;
            nuevo_nodo->anterior = actual;
        }
    }

    // Método para añadir al principio de la lista
    void agregarInicio(Pasajero pa) {
        Nodo_atendidos* nuevo_nodo = new Nodo_atendidos(pa);
        if (cabeza == nullptr) {
            cabeza = nuevo_nodo;
        } else {
            nuevo_nodo->siguiente = cabeza;
            cabeza->anterior = nuevo_nodo;
            cabeza = nuevo_nodo;
        }
    }

    // Método para eliminar un nodo con un dato específico (Pasajero)
    void eliminarNodo(Pasajero pa) {
        Nodo_atendidos* actual = cabeza;
        while (actual != nullptr) {
            if (actual->pasajero.nombre == pa.nombre &&
                actual->pasajero.numero_de_pasaporte == pa.numero_de_pasaporte &&
                actual->pasajero.vuelo == pa.vuelo) {

                if (actual->anterior != nullptr) {
                    actual->anterior->siguiente = actual->siguiente;
                }
                if (actual->siguiente != nullptr) {
                    actual->siguiente->anterior = actual->anterior;
                }
                if (actual == cabeza) {
                    cabeza = actual->siguiente;
                }
                delete actual;
                return;
            }
            actual = actual->siguiente;
        }
    }

    // Método para imprimir la lista (imprime datos relevantes de Pasajero)
    void imprimirLista() {
        Nodo_atendidos* actual = cabeza;
        while (actual != nullptr) {
            std::cout << "Nombre: " << actual->pasajero.nombre << ", ";
            std::cout << "Pasaporte: " << actual->pasajero.numero_de_pasaporte << ", ";
            std::cout << "Vuelo: " << actual->pasajero.vuelo << std::endl;
            std::cout << "Vuelo: " << actual->pasajero.asiento << std::endl;
            std::cout << "------------------------------------------ \n";
            actual = actual->siguiente;
        }
        std::cout << std::endl;
    }

    void ordenarLista() {
        if (cabeza == nullptr || cabeza->siguiente == nullptr) return;

        bool huboIntercambio;
        do {
            huboIntercambio = false;
            Nodo_atendidos* actual = cabeza;
            while (actual->siguiente != nullptr) {
                Nodo_atendidos* siguiente = actual->siguiente;
                if (actual->pasajero.vuelo > siguiente->pasajero.vuelo ||
                    (actual->pasajero.vuelo == siguiente->pasajero.vuelo && actual->pasajero.asiento > siguiente->pasajero.asiento)) {
                    // Intercambio de datos de los pasajeros
                    Pasajero temp = actual->pasajero;
                    actual->pasajero = siguiente->pasajero;
                    siguiente->pasajero = temp;
                    huboIntercambio = true;
                    }
                actual = siguiente;
            }
        } while (huboIntercambio);
    }

    void generarDot(const std::string& nombreArchivo) {
        std::ofstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo para escribir." << std::endl;
            return;
        }

        archivo << "digraph G {" << std::endl;
        archivo << "    node [shape=record];" << std::endl;

        Nodo_atendidos* actual = cabeza;
        int id = 0;
        while (actual != nullptr) {
            archivo << "    nodo" << id << " [label=\"{<anterior> | Nombre: "
                    << actual->pasajero.nombre << "\\nPasaporte: "
                    << actual->pasajero.numero_de_pasaporte << "\\nNacionalidad: "
                    << actual->pasajero.nacionalidad << "\\nVuelo: "
                    << actual->pasajero.vuelo << "\\nAsiento: "
                    << actual->pasajero.asiento << "\\nDestino: "
                    << actual->pasajero.destino << "\\nOrigen: "
                    << actual->pasajero.origen << "\\nEquipaje Facturado: "
                    << actual->pasajero.equipaje_facturado << " | <siguiente>}\"];" << std::endl;
            actual = actual->siguiente;
            id++;
        }

        actual = cabeza;
        id = 0;
        while (actual != nullptr) {
            if (actual->siguiente != nullptr) {
                archivo << "    nodo" << id << ":siguiente -> nodo" << id + 1 << ":anterior;" << std::endl;
                archivo << "    nodo" << id + 1 << ":anterior -> nodo" << id << ":siguiente;" << std::endl;
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

    // Método para buscar un pasajero por número de pasaporte
    bool buscarPorPasaporte(const std::string& numeroPasaporte) {
        Nodo_atendidos* actual = cabeza;
        while (actual != nullptr) {
            if (actual->pasajero.numero_de_pasaporte == numeroPasaporte) {
                std::cout << "------------------------------------------ \n";
                std::cout << "Nombre: " << actual->pasajero.nombre << std::endl;
                std::cout << "Pasaporte: " << actual->pasajero.numero_de_pasaporte << std::endl;
                std::cout << "Vuelo: " << actual->pasajero.vuelo << std::endl;
                std::cout << "Asiento: " << actual->pasajero.asiento << std::endl;
                std::cout << "Destino: " << actual->pasajero.destino << std::endl;
                std::cout << "Origen: " << actual->pasajero.origen << std::endl;
                std::cout << "Equipaje: " << actual->pasajero.equipaje_facturado << std::endl;
                return true; // Se encontró el pasajero
            }
            actual = actual->siguiente;
        }
        return false; // No se encontró el pasajero
    }

};

#endif //LISTADOBLE_H

