//
// Created by PC on 4/9/2023.
//

#include "Empresa.h"
#include <iostream>
#include <algorithm>
#include "conductor.h"
#include "taxi.h"
#include <queue>

Empresa::Empresa() {}
std::queue<Taxi> Empresa::taxis_en_espera;
std::queue<Taxi> Empresa::cola_ruta_;

void Empresa::agregar_taxi() {
    std::cout << std::endl;
    // Pedir al usuario que ingrese los datos del conductor
    Conductor nuevo_conductor;
    std::cout << "Ingrese los datos del conductor:" << std::endl;
    std::cout << "Nombre: ";
    std::cin >> nuevo_conductor.nombre;
    std::cout << "Apellido: ";
    std::cin >> nuevo_conductor.apellido;
    std::cout << "Número de documento de identidad: ";
    std::cin >> nuevo_conductor.numero_documento_identidad;
    std::cout << "Número de seguro social: ";
    std::cin >> nuevo_conductor.numero_seguro_social;
    std::cout << "Número de teléfono: ";
    std::cin >> nuevo_conductor.numero_telefono;
    std::cout << std::endl;

    // Pedir al usuario que ingrese los datos del taxi
    Taxi nuevo_taxi;
    std::cout << "Ingrese los datos del taxi:" << std::endl;
    std::cout << "Placa: ";
    std::cin >> nuevo_taxi.placa;
    std::cout << "Número de motor: ";
    std::cin >> nuevo_taxi.numero_motor;
    std::cout << "Modelo: ";
    std::cin >> nuevo_taxi.modelo;
    std::cout << "Año: ";
    std::cin >> nuevo_taxi.year;

    // Validar los datos del taxi y del conductor
    if (!validar_taxi(nuevo_taxi) || !validar_conductor(nuevo_conductor)) {
        std::cout << "No se puede agregar el taxi." << std::endl;
        return;
    }

    // Asignar la categoría del taxi
    if (nuevo_taxi.year >= 2015) {
        nuevo_taxi.categoria = "Ejecutiva";
    }
    else if (nuevo_taxi.year >= 2010) {
        nuevo_taxi.categoria = "Tradicional";
    }
    else {
        std::cout << "No se puede agregar el taxi. Año inferior a 2010." << std::endl;
        return;
    }

    // Verificar si el taxi ya ha sido registrado
    for (const auto& taxi : taxis_) {
        if (taxi.placa == nuevo_taxi.placa || taxi.numero_motor == nuevo_taxi.numero_motor) {
            std::cout << "No se puede agregar el taxi. Placa o número de motor ya registrado." << std::endl;
            return;
        }
    }

    // Verificar si el conductor ya existe en la empresa
    if (buscar_conductor(nuevo_conductor.numero_documento_identidad)) {
        for (auto& taxi : taxis_) {
            if (taxi.conductor.numero_documento_identidad == nuevo_conductor.numero_documento_identidad) {
                nuevo_taxi.conductor = taxi.conductor;
                break;
            }
        }
    }

    // Si el conductor no existe, agregarlo al taxi y al vector de taxis
    if (nuevo_taxi.conductor.numero_documento_identidad.empty()) {
        nuevo_taxi.conductor = nuevo_conductor;
        taxis_.push_back(nuevo_taxi);
    }

    // Agregar el taxi a la cola de espera
    agregar_a_cola(nuevo_taxi);

    // Mostrar los datos del taxi registrado
    std::cout << "El taxi ha sido registrado correctamente." << std::endl;
    std::cout << "Placa: " << nuevo_taxi.placa << std::endl;
    std::cout << "Número de motor: " << nuevo_taxi.numero_motor << std::endl;
    std::cout << "Modelo: " << nuevo_taxi.modelo << std::endl;
    std::cout << "Año: " << nuevo_taxi.year << std::endl;
    std::cout << "Categoría: " << nuevo_taxi.categoria << std::endl;
    std::cout << "Conductor: " << nuevo_taxi.conductor.nombre << " " << nuevo_taxi.conductor.apellido << std::endl;
    std::cout << "Número de documento de identidad: " << nuevo_taxi.conductor.numero_documento_identidad << std::endl << std::endl;


}

bool Empresa::validar_taxi(Taxi& nuevo_taxi) {
    if (nuevo_taxi.year < 2010) {
        std::cout << "No se puede agregar el taxi. Año inferior a 2010." << std::endl;
        return false;
    }
    return true;
}

bool Empresa::validar_conductor(Conductor& nuevo_conductor) {
    // Verificar si el número de documento de identidad ya está registrado
    if (buscar_conductor(nuevo_conductor.numero_documento_identidad)) {
        std::cout << "No se puede agregar el conductor. Número de documento de identidad ya registrado." << std::endl;
        return false;
    }
    return true;
}

bool Empresa::buscar_conductor(std::string numero_documento_identidad) {
    // Buscar si el número de documento de identidad ya ha sido registrado
    for (const auto& taxi : taxis_) {
        if (taxi.conductor.numero_documento_identidad == numero_documento_identidad) {
            return true;
        }
    }
    return false;
}

void Empresa::agregar_a_cola(Taxi taxi) {
    // Agregar el taxi a la cola de espera
    taxis_en_espera.push(taxi);

    std::cout << "El taxi ha sido agregado a la cola de espera." << std::endl;
}

void Empresa::mostrar_taxis() {
    if (taxis_.empty()) {
        std::cout << "No hay taxis registrados en la empresa." << std::endl;
    }
    else {
        std::cout << "Taxis registrados en la empresa:" << std::endl;
        for (const auto& taxi : taxis_) {
            std::cout << "Placa: " << taxi.placa << std::endl;
            std::cout << "Número de motor: " << taxi.numero_motor << std::endl;
            std::cout << "Modelo: " << taxi.modelo << std::endl;
            std::cout << "Año: " << taxi.year << std::endl;
            std::cout << "Categoría: " << taxi.categoria << std::endl;
            std::cout << "Conductor: " << taxi.conductor.nombre << " " << taxi.conductor.apellido << std::endl;
        }
    }
}


void Empresa::solicitar_taxi() {
    std::string categoria;
    std::string punto_salida;
    std::string destino;
    double costo;
    std::cout << std::endl;
    std::cout << "Ingrese la categoría necesaria (Ejecutiva o Tradicional): ";
    std::cin >> categoria;
    std::cout << "Ingrese el punto de salida: ";
    std::cin >> punto_salida;
    std::cout << "Ingrese el destino: ";
    std::cin >> destino;
    std::cout << "Ingrese el costo del viaje: ";
    std::cin >> costo;
    std::cout << std::endl;

    bool taxi_asignado = false;

    // Buscar un taxi disponible en la cola de espera
    while (!taxis_en_espera.empty()) {
        Taxi taxi = taxis_en_espera.front();
        taxis_en_espera.pop();

        // Verificar si el taxi cumple con los requisitos para el cliente
        if (categoria == "Ejecutiva" && taxi.categoria == "Ejecutiva") {
            if (taxi.year >= 2015) {
                std::cout << "Se ha asignado el siguiente taxi ejecutivo al cliente: " << std::endl;
                std::cout << "Placa: " << taxi.placa << std::endl;
                std::cout << "Conductor: " << taxi.conductor.nombre << " " << taxi.conductor.apellido << std::endl;

                // Agregar el taxi a la cola de ruta
                cola_ruta_.push(taxi);

                taxi_asignado = true;
                break;
            }
        }
        else if (categoria == "Tradicional" && taxi.categoria == "Tradicional") {
            if (taxi.year >= 2010) {
                std::cout << "Se ha asignado el siguiente taxi tradicional al cliente: " << std::endl;
                std::cout << "Placa: " << taxi.placa << std::endl;
                std::cout << "Conductor: " << taxi.conductor.nombre << " " << taxi.conductor.apellido << std::endl;

                // Agregar el taxi a la cola de ruta
                cola_ruta_.push(taxi);

                taxi_asignado = true;
                break;
            }
        }
    }

    if (!taxi_asignado) {
        std::cout << std::endl;

        std::cout << "Lo sentimos, no hay taxis disponibles en este momento." << std::endl;

        std::cout << std::endl;

    }
}

bool Empresa::asignar_taxi(Cliente cliente) {
    // Buscar un taxi disponible en la cola de espera
    while (!taxis_en_espera.empty()) {
        Taxi taxi = taxis_en_espera.front();
        taxis_en_espera.pop();

        // Verificar si el taxi cumple con los requisitos para el cliente
        if (cliente.categoria == "Ejecutiva" && taxi.categoria == "Ejecutiva") {
            if (taxi.year >= 2015) {
                std::cout << "Se ha asignado el siguiente taxi ejecutivo al cliente " << cliente.nombre << ": " << std::endl;
                std::cout << "Placa: " << taxi.placa << std::endl;
                std::cout << "Conductor: " << taxi.conductor.nombre << " " << taxi.conductor.apellido << std::endl;

                // Agregar el taxi a la cola de ruta
                cola_ruta_.push(taxi);

                return true;
            }
        }
        else if (cliente.categoria == "Tradicional" && taxi.categoria == "Tradicional") {
            if (taxi.year >= 2010) {
                std::cout << "Se ha asignado el siguiente taxi tradicional al cliente " << cliente.nombre << ": " << std::endl;
                std::cout << "Placa: " << taxi.placa << std::endl;
                std::cout << "Conductor: " << taxi.conductor.nombre << " " << taxi.conductor.apellido << std::endl;

                // Agregar el taxi a la cola de ruta
                cola_ruta_.push(taxi);

                return true;
            }
        }
    }

    std::cout << "Lo sentimos, no hay taxis disponibles en este momento." << std::endl;
    return false;
}

void Empresa::reingresar_a_cola() {
    if (!cola_ruta_.empty()) {
        Taxi taxi = cola_ruta_.front();
        cola_ruta_.pop();
        taxis_en_espera.push(taxi);
        std::cout << "El taxi con placa " << taxi.placa << " ha sido reingresado a la cola de espera." << std::endl;
    } else {
        std::cout << "No hay taxis en ruta para reingresar a la cola de espera." << std::endl;
    }
}

void Empresa::mostrar_taxis_disponibles() {
    std::cout << "Taxis disponibles en cola de espera:" << std::endl;

    std::cout << std::endl;

    if (taxis_en_espera.empty()) {
        std::cout << std::endl;

        std::cout << "No hay taxis en cola de espera." << std::endl;
        std::cout << std::endl;

    } else {
        std::queue<Taxi> temp = taxis_en_espera; // Hacemos una copia de la cola para no modificar la original
        while (!temp.empty()) {
            Taxi taxi = temp.front();
            temp.pop();
            std::cout << std::endl;

            std::cout << "Placa: " << taxi.placa << std::endl;
            std::cout << "Categoria: " << taxi.categoria << std::endl;
            std::cout << "Año: " << taxi.year << std::endl;
            std::cout << "Modelo: " << taxi.modelo << std::endl;
            std::cout << "Conductor: " << taxi.conductor.nombre << " " << taxi.conductor.apellido << std::endl;
            std::cout << std::endl;
        }
    }
}

void Empresa::mostrar_taxis_en_ruta() {

    std::cout << "Taxis en ruta:" << std::endl;
    std::cout << std::endl;

    if (cola_ruta_.empty()) {
        std::cout << std::endl;

        std::cout << "No hay taxis en ruta." << std::endl;

        std::cout << std::endl;

    } else {
        std::queue<Taxi> temp = cola_ruta_; // Hacemos una copia de la cola para no modificar la original

        while (!temp.empty()) {
            Taxi taxi = temp.front();
            temp.pop();
            std::cout << std::endl;

            std::cout << "Placa: " << taxi.placa << std::endl;
            std::cout << "Categoria: " << taxi.categoria << std::endl;
            std::cout << "Año: " << taxi.year << std::endl;
            std::cout << "Modelo: " << taxi.modelo << std::endl;
            std::cout << "Conductor: " << taxi.conductor.nombre << " " << taxi.conductor.apellido << std::endl;
            std::cout << std::endl;
        }
    }
}

