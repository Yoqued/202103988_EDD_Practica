#ifndef LISTADOBLECIRCULAR_H
#define LISTADOBLECIRCULAR_H

#include "Nodo_avion.h"
#include <iostream>

class ListaDobleCircular {
private:
    Nodo_avion* cabeza;

public:
    ListaDobleCircular() : cabeza(nullptr) {}

    ~ListaDobleCircular() {
        if (!cabeza) return;

        Nodo_avion* actual = cabeza;
        do {
            Nodo_avion* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        } while (actual != cabeza);
    }

    // Metodo para agregar aviones a la lista
    void agregarAvion(Avion a) {
        Nodo_avion* nuevo = new Nodo_avion(a);

        if (!cabeza) {
            cabeza = nuevo;
            cabeza->siguiente = cabeza;
            cabeza->anterior = cabeza;
        } else {
            Nodo_avion* ultimo = cabeza->anterior;
            ultimo->siguiente = nuevo;
            nuevo->anterior = ultimo;
            nuevo->siguiente = cabeza;
            cabeza->anterior = nuevo;
        }
    }

    // Metodo para imprimir la lista de Aviones
    void imprimirLista() {
        if (!cabeza) return;

        Nodo_avion* actual = cabeza;
        do {
            std::cout << "Vuelo: " << actual->avion.vuelo << std::endl;
            std::cout << "Nmero de Registro: " << actual->avion.numero_de_registro << std::endl;
            std::cout << "Modelo: " << actual->avion.modelo << std::endl;
            std::cout << "Fabricante: " << actual->avion.fabricante << std::endl;
            std::cout << "Anio de Fabricaciin: " << actual->avion.ano_fabricacion << std::endl;
            std::cout << "Capacidad: " << actual->avion.capacidad << std::endl;
            std::cout << "Peso Maximo de Despegue: " << actual->avion.peso_max_despegue << std::endl;
            std::cout << "Aerolinea: " << actual->avion.aerolinea << std::endl;
            std::cout << "Estado: " << actual->avion.estado << std::endl;
            std::cout << "--------------------------" << std::endl;
            std::cout << std::endl;
            actual = actual->siguiente;
        } while (actual != cabeza);
    }

    bool estaVacia() const {
        return cabeza == nullptr;
    }

    // Metodo para eliminar un avion por numero de registro
    Avion eliminar(const std::string& numero_de_registro) {
        if (!cabeza) return Avion();  // La lista está vacía

        Nodo_avion* actual = cabeza;
        Nodo_avion* previo = nullptr;

        do {
            if (actual->avion.numero_de_registro == numero_de_registro) {
                Avion avionEliminado = actual->avion;

                if (actual->siguiente == actual) {
                    // Solo hay un nodo en la lista
                    delete actual;
                    cabeza = nullptr;
                } else {
                    // Hay más de un nodo en la lista
                    if (actual == cabeza) {
                        cabeza = actual->siguiente;
                    }
                    previo = actual->anterior;
                    previo->siguiente = actual->siguiente;
                    actual->siguiente->anterior = previo;

                    delete actual;
                }

                return avionEliminado;
            }
            actual = actual->siguiente;
        } while (actual != cabeza);

        return Avion();  // No se encontró el avión con el número de registro dado
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

        if (cabeza) {
            Nodo_avion* actual = cabeza;
            int id = 0;
            do {
                archivo << "    nodo" << id << " [label=\"{|Vuelo: "
                        << actual->avion.vuelo << "\\nNúmero de Registro: "
                        << actual->avion.numero_de_registro << "\\nModelo: "
                        << actual->avion.modelo << "\\nFabricante: "
                        << actual->avion.fabricante << "\\nAño: "
                        << actual->avion.ano_fabricacion << "\\nCapacidad: "
                        << actual->avion.capacidad << "\\nPeso Máximo: "
                        << actual->avion.peso_max_despegue << "\\nAerolínea: "
                        << actual->avion.aerolinea << "\\nEstado: "
                        << actual->avion.estado << "|}\"];" << std::endl;
                if (actual->siguiente != cabeza) {
                    archivo << "    nodo" << id << " -> nodo" << id + 1 << ";" << std::endl;
                    archivo << "    nodo" << id + 1 << " -> nodo" << id << ";" << std::endl;
                } else {
                    archivo << "    nodo" << id << " -> nodo0;" << std::endl;
                    archivo << "    nodo0 -> nodo" << id << ";" << std::endl;
                }
                actual = actual->siguiente;
                id++;
            } while (actual != cabeza);
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

};

#endif // LISTADOBLECIRCULAR_H

