//
// Created by PC on 4/9/2023.
//

#include "Empresa.h"
#include <iostream>
#include <algorithm>
#include "conductor.h"
#include "taxi.h"
#include <queue>
#include <fstream>
#include <sstream>


// Colores ANSI
#define ANSI_RESET "\033[0m"
#define ANSI_BOLD "\033[1m"
#define ANSI_GREEN "\033[32m"
#define ANSI_CYAN "\033[36m"
#define ANSI_RESET "\033[0m"
#define ANSI_YELLOW "\033[33m"
#define ANSI_RED "\033[31m"

Empresa::Empresa() {}

std::queue<Taxi> Empresa::taxis_en_espera;
std::queue<Taxi> Empresa::cola_ruta_;

void Empresa::cargar_datos() {
    // Cargar los datos de los taxis desde el archivo
    std::ifstream archivo_taxis("taxis.txt");
    if (archivo_taxis.is_open()) {
        std::string linea;
        while (std::getline(archivo_taxis, linea)) {
            std::stringstream ss(linea);
            std::string dato;
            std::vector<std::string> datos_taxi;
            while (std::getline(ss, dato, ',')) {
                datos_taxi.push_back(dato);
            }

            // Crear un objeto Taxi y agregarlo a la cola de espera
            Taxi taxi;
            taxi.placa = datos_taxi[0];
            taxi.categoria = datos_taxi[1];
            taxi.year = std::stoi(datos_taxi[2]);
            taxi.modelo = datos_taxi[3];
            taxi.numero_motor = datos_taxi[4];
            taxi.conductor.nombre = datos_taxi[5];
            taxi.conductor.apellido = datos_taxi[6];
            taxi.conductor.numero_documento_identidad= datos_taxi[7];
            taxi.conductor.numero_seguro_social = datos_taxi[8];
            taxi.conductor.numero_telefono = datos_taxi[9];
            taxis_en_espera.push(taxi);
            taxis_.push_back(taxi);

        }
        archivo_taxis.close();
    }

}


void Empresa::limparPantalla() {
    system("cls");  // Comando para limpiar la pantalla en Windows
}

void Empresa::pausa() {
#ifdef _WIN32
    system("pause");  // Comando para pausar en Windows
#else
    system("read -p 'Presione Enter para continuar...'");  // Comando para pausar en Linux
#endif
}

void Empresa::agregar_taxi() {
    limparPantalla();
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

    limparPantalla();
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
    limparPantalla();
    // Validar los datos del taxi y del conductor
    if (!validar_taxi(nuevo_taxi) || !validar_conductor(nuevo_conductor)) {
        std::cout << "No se puede agregar el taxi." << std::endl;
        return;
    }

    // Asignar la categoría del taxi
    if (nuevo_taxi.year >= 2015) {
        nuevo_taxi.categoria = "Ejecutiva";
    } else if (nuevo_taxi.year >= 2010) {
        nuevo_taxi.categoria = "Tradicional";
    } else {
        std::cout << "No se puede agregar el taxi. Año inferior a 2010." << std::endl;
        return;
    }

    // Verificar si el taxi ya ha sido registrado
    for (const auto &taxi: taxis_) {
        if (taxi.placa == nuevo_taxi.placa || taxi.numero_motor == nuevo_taxi.numero_motor) {
            std::cout << "No se puede agregar el taxi. Placa o número de motor ya registrado." << std::endl;
            return;
        }
    }

    // Verificar si el conductor ya existe en la empresa
    if (buscar_conductor(nuevo_conductor.numero_documento_identidad)) {
        for (auto &taxi: taxis_) {
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
    std::cout << "Número de documento de identidad: " << nuevo_taxi.conductor.numero_documento_identidad << std::endl;

    // Guardar los datos en un archivo de texto
    std::ofstream archivo("taxis.txt", std::ios::app);
    archivo << nuevo_taxi.placa << "," << nuevo_taxi.categoria << "," << nuevo_taxi.year << "," << nuevo_taxi.modelo << "," << nuevo_taxi.numero_motor << ","
            << nuevo_taxi.conductor.nombre << "," << nuevo_taxi.conductor.apellido << "," << nuevo_taxi.conductor.numero_documento_identidad << ","
            << nuevo_taxi.conductor.numero_seguro_social << "," << nuevo_taxi.conductor.numero_telefono << std::endl;
    archivo.close();

    pausa();
    limparPantalla();

}

bool Empresa::validar_taxi(Taxi &nuevo_taxi) {
    if (nuevo_taxi.year < 2010) {
        std::cout << "No se puede agregar el taxi. Año inferior a 2010." << std::endl;
        return false;
    }
    return true;
}

bool Empresa::validar_conductor(Conductor &nuevo_conductor) {
    // Verificar si el número de documento de identidad ya está registrado
    if (buscar_conductor(nuevo_conductor.numero_documento_identidad)) {
        std::cout << "No se puede agregar el conductor. Número de documento de identidad ya registrado." << std::endl;
        return false;
    }
    return true;
}

bool Empresa::buscar_conductor(std::string numero_documento_identidad) {
    // Buscar si el número de documento de identidad ya ha sido registrado
    for (const auto &taxi: taxis_) {
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
        pausa();
        limparPantalla();
    } else {
        limparPantalla();
        std::cout << "Taxis registrados en la empresa:" << std::endl;
        for (const auto &taxi: taxis_) {
            std::cout << "Placa: " << taxi.placa << std::endl;
            std::cout << "Número de motor: " << taxi.numero_motor << std::endl;
            std::cout << "Modelo: " << taxi.modelo << std::endl;
            std::cout << "Año: " << taxi.year << std::endl;
            std::cout << "Categoría: " << taxi.categoria << std::endl;
            std::cout << "Conductor: " << taxi.conductor.nombre << " " << taxi.conductor.apellido << std::endl;
            std::cout << "  " << std::endl;
        }
        pausa();
        limparPantalla();
    }

}

void Empresa::finalizar_viaje(double costo) {


    // Obtener el taxi en ruta
    Taxi taxi;

    // Agregar el taxi nuevamente a la cola de espera
    reingresar_a_cola();
    Cliente cliente;
    // Mostrar datos relevantes del viaje
    std::cout << "------ VIAJE FINALIZADO ------" << std::endl;
    std::cout << "Costo del viaje: $" << costo << std::endl;

    // Simulación de cobro
    std::cout << "Cobro realizado exitosamente." << std::endl;

    pausa();
    limparPantalla();
    mostrar_menu_cliente();
}

void Empresa::cancelar_viaje() {



    // Agregar el taxi nuevamente a la cola de espera
    reingresar_a_cola();
    Cliente cliente;
    std::cout << "Viaje cancelado." << std::endl;
    pausa();
    limparPantalla();
    mostrar_menu_cliente();
}


void Empresa::solicitar_taxi() {
    limparPantalla();
    Cliente cliente;
    std::cout << "Ingrese su nombre: ";
    std::cin >> cliente.nombre;
    std::cout << "Ingrese la categoria de taxi que desea (Ejecutiva o Tradicional): ";
    std::cin >> cliente.categoria;
    std::cout << "Ingrese el punto de salida del viaje: ";
    std::cin >> cliente.punto_salida;
    std::cout << "Ingrese el destino del viaje: ";
    std::cin >> cliente.destino;

    // Calculamos el costo del viaje según la categoría del taxi
    double costo = 0;
    if (cliente.categoria == "Ejecutiva") {
        costo = 50; // Costo base de la categoría ejecutiva
    } else if (cliente.categoria == "Tradicional") {
        costo = 25; // Costo base de la categoría tradicional
    }

    limparPantalla();
    // Buscamos el primer taxi disponible en la cola de espera de la categoría solicitada
    bool taxi_asignado = asignar_taxi(cliente);
    if (taxi_asignado) {
        std::cout << "Taxi asignado exitosamente." << std::endl;
        std::cout << "Costo del viaje: $" << costo << std::endl;

        int opcion = 0;
        while (opcion != 5) {
            std::cout << "------ VIAJE EN CURSO ------" << std::endl;
            std::cout << "1. Finalizar viaje" << std::endl;
            std::cout << "2. Cancelar viaje" << std::endl;
            std::cout << "3. Mostrar taxis en ruta" << std::endl;
            std::cout << "4. Mostrar taxis disponibles" << std::endl;
            std::cout << "Ingrese la opcion deseada: ";
            std::cin >> opcion;

            switch (opcion) {
                case 1:
                    limparPantalla();
                    finalizar_viaje(costo);
                    break;
                case 2:
                    limparPantalla();
                    cancelar_viaje();
                    break;
                case 3:
                    limparPantalla();
                    mostrar_taxis_en_ruta();
                    break;
                case 4:
                    mostrar_taxis_disponibles();
                    limparPantalla();
                    break;
                default:
                    std::cout << "Opcion no valida. Por favor, intente de nuevo." << std::endl;
                    break;
            }
        }
    } else {
        std::cout << "Lo sentimos, no hay taxis disponibles en este momento." << std::endl;
        std::cout << "Por favor, intente de nuevo más tarde." << std::endl;
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
                std::cout << "Se ha asignado el siguiente taxi ejecutivo al cliente " << cliente.nombre << ": "
                          << std::endl;
                std::cout << "Placa: " << taxi.placa << std::endl;
                std::cout << "Conductor: " << taxi.conductor.nombre << " " << taxi.conductor.apellido << std::endl;

                // Agregar el taxi a la cola de ruta
                cola_ruta_.push(taxi);
                return true;
            }
        } else if (cliente.categoria == "Tradicional" && taxi.categoria == "Tradicional") {
            if (taxi.year >= 2010) {
                std::cout << "Se ha asignado el siguiente taxi tradicional al cliente " << cliente.nombre << ": "
                          << std::endl;
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
    limparPantalla();

    std::cout << "Taxis disponibles en cola de espera:" << std::endl;

    if (taxis_en_espera.empty()) {
        std::cout << std::endl;

        std::cout << "No hay taxis en cola de espera." << std::endl;
        std::cout << std::endl;
        limparPantalla();

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

    pausa();

}

void Empresa::mostrar_taxis_en_ruta() {
    limparPantalla();

    std::cout << "Taxis en ruta:" << std::endl;
    if (cola_ruta_.empty()) {
        std::cout << std::endl;

        std::cout << "No hay taxis en ruta." << std::endl;

        std::cout << std::endl;
        pausa();
        limparPantalla();

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


void Empresa::mostrar_menu_cliente() {
    int opcion = 0;
    while (opcion != 4) {
        limparPantalla();
        std::cout << "**************************************************************" << std::endl;
        std::cout << ANSI_BOLD << ANSI_CYAN << "*************         MENU CLIENTE         *******************" << ANSI_RESET << std::endl;
        std::cout << "**************************************************************" << std::endl;
        std::cout << ANSI_BOLD << ANSI_YELLOW << "*********    1. Ver taxis disponibles               ***********" << ANSI_RESET << std::endl;
        std::cout << ANSI_BOLD << ANSI_YELLOW << "*********    2. Ver taxis en ruta                   ***********" << ANSI_RESET << std::endl;
        std::cout << ANSI_BOLD << ANSI_YELLOW << "*********    3. Solicitar taxi                      ***********" << ANSI_RESET << std::endl;
        std::cout << ANSI_BOLD << ANSI_YELLOW << "*********    4. Volver al menú principal            ***********" << ANSI_RESET << std::endl;
        std::cout << "**************************************************************" << std::endl;
        std::cout << "Ingrese la opción deseada: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                limparPantalla();
                mostrar_taxis_disponibles();
                break;
            case 2:
                limparPantalla();
                mostrar_taxis_en_ruta();
                break;
            case 3:
                limparPantalla();
                solicitar_taxi();
                break;
            case 4:
                limparPantalla();
                std::cout << "Volviendo al menú principal..." << std::endl;
                mostrar_menus();
                break;
            default:
                std::cout << "Opcion no valida. Por favor, intente de nuevo." << std::endl;
                break;
        }

        pausa();
    }
}


void Empresa::mostrar_menu_principal() {
    int opcion = 0;
    while (opcion != 6) {
        limparPantalla();

        std::cout << "**************************************************************" << std::endl;
        std::cout << ANSI_BOLD << ANSI_CYAN << "**********************   TrueDrive   *************************" << ANSI_RESET << std::endl;
        std::cout << "**************************************************************" << std::endl;
        std::cout << ANSI_BOLD << "**********    1. Agregar taxi                                *" << ANSI_RESET << std::endl;
        std::cout << ANSI_BOLD << "**********    2. Solicitar taxi                              *" << ANSI_RESET << std::endl;
        std::cout << ANSI_BOLD << "**********    3. Mostrar taxis disponibles                   *" << ANSI_RESET << std::endl;
        std::cout << ANSI_BOLD << "**********    4. Mostrar taxis en ruta                       *" << ANSI_RESET << std::endl;
        std::cout << ANSI_BOLD << "**********    5. Mostrar todos los taxis                     *" << ANSI_RESET << std::endl;
        std::cout << ANSI_BOLD << "**********    6. Salir                                       *" << ANSI_RESET << std::endl;
        std::cout << "**************************************************************" << std::endl;


        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                limparPantalla();
                agregar_taxi();
                break;
            case 2:
                limparPantalla();
                solicitar_taxi();
                break;
            case 3:
                limparPantalla();
                mostrar_taxis_disponibles();
                break;
            case 4:
                limparPantalla();
                mostrar_taxis_en_ruta();
                break;
            case 5:
                limparPantalla();
                mostrar_taxis();
                break;
            case 6:
                std::cout << "Volviendo al menú principal..." << std::endl;
                mostrar_menus();
                break;
            default:
                std::cout << "Opcion invalida, intente de nuevo." << std::endl;
                break;
        }
    }
}

void Empresa::mostrar_menus() {
    int opcion = 0;
    while (opcion != 3) {
        limparPantalla();
        std::cout << ANSI_CYAN << "**************************************************************" << ANSI_RESET << std::endl;
        std::cout << ANSI_BOLD << "------ " << ANSI_CYAN << "TRUEDRIVE" << ANSI_RESET << ANSI_BOLD << " ------" << std::endl;
        std::cout << ANSI_BOLD << ANSI_GREEN << "1. Menú cliente" << ANSI_RESET << std::endl;
        std::cout << ANSI_BOLD << ANSI_GREEN << "2. Menú principal" << ANSI_RESET << std::endl;
        std::cout << ANSI_BOLD << ANSI_GREEN << "3. Salir" << ANSI_RESET << std::endl;
        std::cout << ANSI_CYAN << "**************************************************************" << ANSI_RESET << std::endl;
        std::cout << "Ingrese la opción deseada: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                limparPantalla();
                mostrar_menu_cliente();
                break;
            case 2:
                limparPantalla();
                mostrar_menu_principal();
                break;
            case 3:
                std::cout << "Gracias por usar nuestro servicio de taxis. Hasta luego!" << std::endl;
                break;
            default:
                std::cout << "Opcion no valida. Por favor, intente de nuevo." << std::endl;
                break;
        }

    }
}
