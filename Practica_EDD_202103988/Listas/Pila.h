#ifndef PILA_H
#define PILA_H

#include "Nodo_equipaje.h"
#include <iostream>

class Pila {
private:
    Nodo_equipaje* tope;

public:
    Pila() : tope(nullptr) {}

    ~Pila() {
        while (!esta_vacia()) {
            desapilar();
        }
    }

    bool esta_vacia() const {
        return tope == nullptr;
    }

    void apilar(const Equipaje& equipaje) {
        Nodo_equipaje* nuevo_nodo = new Nodo_equipaje(equipaje);
        if (esta_vacia()) {
            tope = nuevo_nodo;
        } else {
            nuevo_nodo->siguiente = tope;
            tope->anterior = nuevo_nodo;
            tope = nuevo_nodo;
        }
    }

    Equipaje desapilar() {
        if (esta_vacia()) {
            std::cerr << "La pila está vacía" << std::endl;
            throw std::runtime_error("Pila vacía");
        } else {
            Nodo_equipaje* nodo_a_eliminar = tope;
            Equipaje equipaje_desapilado = nodo_a_eliminar->equipaje;
            tope = tope->siguiente;
            if (tope != nullptr) {
                tope->anterior = nullptr;
            }
            delete nodo_a_eliminar;
            return equipaje_desapilado;
        }
    }

    Equipaje ver_tope() const {
        if (esta_vacia()) {
            std::cerr << "La pila está vacía" << std::endl;
            throw std::runtime_error("Pila vacía");
        } else {
            return tope->equipaje;
        }
    }

    void imprimir() const {
        if (esta_vacia()) {
            std::cout << "La pila está vacía" << std::endl;
        } else {
            Nodo_equipaje* actual = tope;
            while (actual != nullptr) {
                std::cout << actual->equipaje.nombre << std::endl;
                std::cout << actual->equipaje.numero_de_pasaporte << std::endl;
                std::cout << actual->equipaje.equipaje << std::endl;
                std::cout << "------------------------------------------ \n";
                actual = actual->siguiente;
            }
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

        Nodo_equipaje* actual = tope;
        int id = 0;
        while (actual != nullptr) {
            archivo << "    nodo" << id << " [label=\"{<siguiente> | Nombre: "
                    << actual->equipaje.nombre << "\\nPasaporte: "
                    << actual->equipaje.numero_de_pasaporte << "\\nEquipaje: "
                    << actual->equipaje.equipaje << " | <anterior>}\"];" << std::endl;
            if (actual->siguiente != nullptr) {
                archivo << "    nodo" << id << ":siguiente -> nodo" << id + 1 << ":anterior;" << std::endl;
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
};

#endif // PILA_H

