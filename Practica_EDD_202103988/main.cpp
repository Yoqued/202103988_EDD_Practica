#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include <cctype>
#include <cstdlib>
#include <sstream>

#include "Listas/ListaDobleCircular.h"
#include "Listas/Cola.h"
#include "Listas/Pila.h"
#include "Listas/ListaDoble.h"

using json = nlohmann::json;

ListaDobleCircular avionesDisponiles;
ListaDobleCircular avionesMantenimiento;
Cola colaPasajeros;
Pila pilaEquipaje;
ListaDoble pasajeroAtendido;

// Declaración de funciones
void cargarAviones();
void cargarPasajeros();
void cargarMovimientos();
void consultarPasajeros();
void visualizarReportes();
void clearScreen();

int main() {

    int opcion;

    do {
        // Mostrar el menú
        std::cout << "\n";
        std::cout << "------------- Menu Principal ------------- \n";
        std::cout << "1. Carga de aviones \n";
        std::cout << "2. Carga de pasajeros \n";
        std::cout << "3. Carga de movimientos \n";
        std::cout << "4. Consultar pasajeros \n";
        std::cout << "5. Visualizar reportes \n";
        std::cout << "6. Salir \n";
        std::cout << "------------------------------------------ \n";
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;

        // Manejar la opción seleccionada
        switch(opcion) {
            case 1:
                cargarAviones();
            break;
            case 2:
                cargarPasajeros();
            break;
            case 3:
                cargarMovimientos();
            break;
            case 4:
                consultarPasajeros();
            break;
            case 5:
                visualizarReportes();
            break;
            case 6:
                std::cout << "Saliendo del programa...\n";
            break;
            default:
                std::cout << "Opción no válida. Intente de nuevo.\n";
        }

    } while(opcion != 6);

    return 0;
}

// Definiciones de funciones
void cargarAviones() {
    clearScreen();
    std::string ruta_aviones;
    std::cout << std::endl;
    std::cout << "------------------------------------------ \n";
    std::cout << "Ingrese ruta de archivo de Aviones: ";
    std::cin >> ruta_aviones;
    // Abrir el archivo JSON
    std::ifstream input(ruta_aviones);
    if (!input.is_open()) {
        std::cerr << "No se pudo abrir el archivo aviones.json" << std::endl;
    }else {
        // Leer el contenido del archivo en un objeto JSON
        json j;
        input >> j;

        // Asegurarse de que el JSON es una lista de objetos
        if (!j.is_array()) {
            std::cerr << "El archivo JSON no contiene una lista de objetos" << std::endl;
        }else {
            // Iterar a través de la lista y mostrar el contenido de cada objeto
            for (const auto& item : j) {

                std::string cadena = item["estado"];

                // Convertir la cadena a minúsculas
                for (char &c : cadena) {
                    c = std::tolower(c);
                }
                if(cadena.compare("disponible")==0) {
                    Avion avion = {item["vuelo"], item["numero_de_registro"], item["modelo"], item["fabricante"],
                        item["ano_fabricacion"], item["capacidad"], item["peso_max_despegue"], item["aerolinea"],
                        item["estado"]};
                    avionesDisponiles.agregarAvion(avion);
                }
                if(cadena.compare("mantenimiento")==0) {
                    Avion avion = {item["vuelo"], item["numero_de_registro"], item["modelo"], item["fabricante"],
                        item["ano_fabricacion"], item["capacidad"], item["peso_max_despegue"], item["aerolinea"],
                        item["estado"]};
                    avionesMantenimiento.agregarAvion(avion);
                }
            }
        }
        std::cout << "Archivo de Aviones leeido con Exito \n";
    }
}

void cargarPasajeros() {
    clearScreen();
    std::string ruta_pasajeros;
    std::cout << std::endl;
    std::cout << "------------------------------------------ \n";
    std::cout << "Ingrese ruta de archivo de Pasajeros: ";
    std::cin >> ruta_pasajeros;
    // Abrir el archivo JSON
    std::ifstream input(ruta_pasajeros);
    if (!input.is_open()) {
        std::cerr << "No se pudo abrir el archivo aviones.json" << std::endl;
    }else {
        // Leer el contenido del archivo en un objeto JSON
        json j;
        input >> j;

        // Asegurarse de que el JSON es una lista de objetos
        if (!j.is_array()) {
            std::cerr << "El archivo JSON no contiene una lista de objetos" << std::endl;
        }else {
            // Iterar a través de la lista y mostrar el contenido de cada objeto
            for (const auto& item : j) {
                Pasajero pasajero = {item["nombre"], item["nacionalidad"], item["numero_de_pasaporte"], item["vuelo"],
                item["asiento"], item["destino"], item["origen"],item["equipaje_facturado"] };
                colaPasajeros.encolar(pasajero);
            }
        }
    }
    std::cout << "Archivo de Pasajeros leeido con Exito \n";
}

void cargarMovimientos() {
    clearScreen();
    std::string ruta_movimientos;
    std::cout << std::endl;
    std::cout << "------------------------------------------ \n";
    std::cout << "Ingrese ruta de archivo de Pasajeros: ";
    std::cin >> ruta_movimientos;
    std::ifstream archivo(ruta_movimientos);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
    }else {
        std::string linea;
        while (getline(archivo, linea)) {
            if(linea.compare("IngresoEquipajes;")==0) {
                if(colaPasajeros.esta_vacia()) {
                    std::cout << "No se puede hacer movimientos; No hay pasajeros"<< std::endl;
                    std::cout << "------------------------------------------ \n";
                    break;
                }else {
                    //std::cout << linea << std::endl;
                    Pasajero data = colaPasajeros.desencolar();
                    if(data.equipaje_facturado == 0) {
                        Pasajero datos = {data.nombre, data.nacionalidad, data.numero_de_pasaporte, data.vuelo, data.asiento, data.destino, data.origen, data.equipaje_facturado};
                        pasajeroAtendido.agregarFinal(datos);
                    }else {
                        Pasajero datos = {data.nombre, data.nacionalidad, data.numero_de_pasaporte, data.vuelo, data.asiento, data.destino, data.origen, data.equipaje_facturado};
                        pasajeroAtendido.agregarFinal(datos);
                        Equipaje equi = {data.nombre, data.numero_de_pasaporte, data.equipaje_facturado};
                        pilaEquipaje.apilar(equi);
                    }
                }
            }else {
                std::stringstream ss(linea);
                std::string token;
                std::string comando, accion, codigo;
                int contador = 0;

                while (getline(ss, token, ',')) {
                    switch (contador) {
                        case 0: comando = token; break;
                        case 1: accion = token; break;
                        case 2: codigo = token; break;
                        default: break;
                    }
                    contador++;
                }
                if(comando.compare("MantenimientoAviones") == 0) {
                    if(accion.compare("Salida") == 0) {
                        codigo.erase(std::remove(codigo.begin(), codigo.end(), ';'), codigo.end());
                        Avion avi = avionesMantenimiento.eliminar(codigo);
                        Avion aviN = {avi.vuelo, avi.numero_de_registro, avi.modelo, avi.fabricante, avi.ano_fabricacion, avi.capacidad, avi.peso_max_despegue, avi.aerolinea, "Disponible"};
                        avionesDisponiles.agregarAvion(aviN);
                    }else if(accion.compare("Ingreso") == 0) {
                        codigo.erase(std::remove(codigo.begin(), codigo.end(), ';'), codigo.end());
                        Avion avi = avionesDisponiles.eliminar(codigo);
                        Avion aviN = {avi.vuelo, avi.numero_de_registro, avi.modelo, avi.fabricante, avi.ano_fabricacion, avi.capacidad, avi.peso_max_despegue, avi.aerolinea, "Mantenimiento"};
                        avionesMantenimiento.agregarAvion(aviN);
                    }
                }
            }
        }
        archivo.close();
        std::cout << "Archivo de movimientos leeido con Exito \n";
    }
}

void consultarPasajeros() {
    clearScreen();
    std::string pasport;
    std::cout << std::endl;
    std::cout << "------------------------------------------ \n";
    std::cout << "Ingrese numero de Pasaporte de Pasajero: ";
    std::cin >> pasport;
    if(colaPasajeros.buscar_por_pasaporte(pasport)) {

    }else {
        if (pasajeroAtendido.buscarPorPasaporte(pasport)) {

        }else {
            std::cout << std::endl;
            std::cout << "------------------------------------------ \n";
            std::cout << "No se encontro Pasajero";
        }

    }

}

void visualizarReportes() {
    clearScreen();
    // Aquí iría el código para visualizar reportes
    int opcion;
    do {
        std::cout << "\n";
        std::cout << "--------- Menu de Visualizacion de Reportes ---------\n";
        std::cout << "1. Lista de aviones disponibles\n";
        std::cout << "2. Lista de aviones en mantenimiento\n";
        std::cout << "3. Cola de registro\n";
        std::cout << "4. Pila de equipaje\n";
        std::cout << "5. Lista de pasajeros\n";
        std::cout << "6. Salir\n";
        std::cout << "-----------------------------------------------------\n";
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;

        switch(opcion) {
            case 1:
            avionesDisponiles.generarDot("Reporte_Disponibles");
            break;
            case 2:
            avionesMantenimiento.generarDot("Reporte_Mantenimiento");
            break;
            case 3:
            colaPasajeros.generarDot("Reporte_Cola_Pasajeros");
            break;
            case 4:
            pilaEquipaje.generarDot("Reporte_Equipaje");
            break;
            case 5:
            pasajeroAtendido.generarDot("Reporte_Atendidos");
            break;
            case 6:
                std::cout << "Saliendo del menu de reportes...\n";
            break;
            default:
                std::cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while(opcion != 6);
}

void clearScreen() {
    system("cls");
}