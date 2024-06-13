cmake_minimum_required(VERSION 3.10)
project(ReadJSON)

set(CMAKE_CXX_STANDARD 11)

# Incluye el archivo de configuración de vcpkg
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Encuentra el paquete nlohmann_json
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(ReadJSON main.cpp
        Listas/ListaDobleCircular.h
        Listas/Avion.h
        Listas/Nodo_avion.h
        Listas/Pasajero.h
        Listas/Nodo_pasajero.h
        Listas/Cola.h
        Listas/Equipaje.h
        Listas/Nodo_equipaje.h
        Listas/Pila.h
        Listas/Nodo_atendidos.h
        Listas/ListaDoble.h)

# Enlaza la biblioteca nlohmann_json con tu ejecutable
target_link_libraries(ReadJSON PRIVATE nlohmann_json::nlohmann_json)


